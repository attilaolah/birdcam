package main

import (
	"context"
	"errors"
	"fmt"
	"os"
	"os/signal"
	"strings"
	"syscall"
	"time"

	"github.com/go-ble/ble"
	"github.com/go-ble/ble/linux"
	"tinygo.org/x/bluetooth"
)

// LocalName advertised by this camera model.
const CamName = "A900"

// UUID generates Nikon vendor-specific UUIDs.
func UUID(b uint16) ble.UUID {
	return ble.MustParse(fmt.Sprintf("0000%04x-3dd4-4255-8d62-6dc7b9bd5561", b))
}

var (
	// COOLPIX A900 vendor-specific stuff.
	// These are mostly reverse-engineered, so take them with a grain of salt.

	// Services advertised by this camera model.

	// >>> Handle, ValueHandle:
	GAP        = ble.NewService(ble.GAPUUID)        // 0x01 0x07
	GATT       = ble.NewService(ble.GATTUUID)       // 0x0c 0x0f
	NIKON      = ble.NewService(UUID(0xDE00))       // 0x40 0x5a // https://hal.inria.fr/hal-02394629/document @ page 9
	DeviceInfo = ble.NewService(ble.DeviceInfoUUID) // 0x6f 0x77

	// GAPP >>> Handle, ValueHandle, EndHandle (IFF != ValueHandle)
	DeviceName     = ble.NewCharacteristic(ble.DeviceNameUUID)     // 0x02 0x03
	Appearance     = ble.NewCharacteristic(ble.AppearanceUUID)     // 0x04 0x05
	PeferredParams = ble.NewCharacteristic(ble.PeferredParamsUUID) // 0x06 0x07

	// GATT >>> Handle, ValueHandle, EndHandle (IFF != ValueHandle)
	ServiceChanged = ble.NewCharacteristic(ble.ServiceChangedUUID) // 0x0d 0x0e 0x0f

	// DeviceInfo >>> Handle, ValueHandle, EndHandle (IFF != ValueHandle)
	ManufacturerNameString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDManufacturerNameString.Get16Bit())) // 0x70 0x71
	FirmwareRevisionString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDFirmwareRevisionString.Get16Bit())) // 0x72 0x73
	SoftwareRevisionString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDSoftwareRevisionString.Get16Bit())) // 0x74 0x75
	ModelNumberString      = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDModelNumberString.Get16Bit()))      // 0x76 0x77

	// Characteristics advertised by this camera model (mostly reverse-engineered).
	// Some are also listed here: https://dslrdashboard.info/phpBB3/viewtopic.php?p=7796#p7796

	// NIKON >>> Handle, ValueHandle, EndHandle (IFF != ValueHandle)
	Authentication          = ble.NewCharacteristic(UUID(0x2000)) // 0x41 0x42 0x43
	PowerControl            = ble.NewCharacteristic(UUID(0x2001)) // 0x44 0x45
	ClientDeviceName        = ble.NewCharacteristic(UUID(0x2002)) // 0x46 0x47
	ServerDeviceName        = ble.NewCharacteristic(UUID(0x2003)) // 0x48 0x49
	ConnectionConfiguration = ble.NewCharacteristic(UUID(0x2004)) // 0x4a 0x4b
	ConnectionEstablishment = ble.NewCharacteristic(UUID(0x2005)) // 0x4c 0x4d
	CurrentTime             = ble.NewCharacteristic(UUID(0x2006)) // 0x4e 0x4f
	LocationInformation     = ble.NewCharacteristic(UUID(0x2007)) // 0x50 0x51
	LSSControlPoint         = ble.NewCharacteristic(UUID(0x2008)) // 0x52 0x53 0x54
	LSSFeature              = ble.NewCharacteristic(UUID(0x2009)) // 0x55 0x56
	BatteryLevel            = ble.NewCharacteristic(UUID(0x2A19)) // 0x57 0x58
	LSSSerialNumberString   = ble.NewCharacteristic(UUID(0x200b)) // 0x59 5x5a

	// Advertised descriptors:
	// ClientCharacteristicConfig [0x2902] at handles: 0x0f, 0x43, 0x54.
)

type DeviceInformation struct {
	ManufacturerName string
	ModelNumber      string
	SerialNumber     string
	SoftwareRevision string
	FirmwareRevision string
}

type A900 struct {
	ble.Client

	DeviceInformation
	TxPower int
}

func Connect(ctx context.Context) (cam *A900, err error) {
	var txp int
	cli, err := ble.Connect(ctx, func(a ble.Advertisement) bool {
		if a.LocalName() != CamName || !a.Connectable() {
			return false
		}
		for _, s := range a.Services() {
			if NIKON.UUID.Equal(s) {
				txp = a.TxPowerLevel()
				return true
			}
		}
		return false
	})
	if err != nil {
		return nil, fmt.Errorf("failed to connect to camera: %w", err)
	}

	defer func() {
		if err == nil {
			return
		}
		// Something went wrong, close the connection:
		if cerr := cli.CancelConnection(); cerr != nil {
			err = fmt.Errorf("%w; failed to close connection: %w", err, cerr)
		}
	}()

	info := DeviceInformation{}
	if info.ManufacturerName, err = ReadCharacteristic(cli, ManufacturerNameString); err != nil {
		err = fmt.Errorf("failed to read manufacturer name: %w", err)
		return
	}
	if info.ModelNumber, err = ReadCharacteristic(cli, ModelNumberString); err != nil {
		err = fmt.Errorf("failed to read model number: %w", err)
		return
	}
	if info.SoftwareRevision, err = ReadCharacteristic(cli, SoftwareRevisionString); err != nil {
		err = fmt.Errorf("failed to read software revision: %w", err)
		return
	}
	if info.FirmwareRevision, err = ReadCharacteristic(cli, FirmwareRevisionString); err != nil {
		err = fmt.Errorf("failed to read firmware revision: %w", err)
		return
	}
	if info.SerialNumber, err = ReadCharacteristic(cli, LSSSerialNumberString); err != nil {
		err = fmt.Errorf("failed to read serial number: %w", err)
		return
	}

	return &A900{
		Client:            cli,
		DeviceInformation: info,
		TxPower:           txp,
	}, nil
}

func ReadCharacteristic(cli ble.Client, c *ble.Characteristic) (string, error) {
	p := cli.Profile()
	if p == nil {
		var err error
		if p, err = cli.DiscoverProfile(false); err != nil {
			return "", fmt.Errorf("failed to discover profile: %w", err)
		}
	}

	if c := p.FindCharacteristic(c); c == nil {
		return "", errors.New("characteristic not found")
	} else if c.Property|ble.CharRead == 0 {
		return "", errors.New("characteristic cannot be read")
	} else {
		if buf, err := cli.ReadCharacteristic(c); err != nil {
			return "", fmt.Errorf("failed to read characteristic: %w", err)
		} else {
			return strings.TrimSpace(strings.Trim(string(buf), "\x00")), nil
		}
	}
}

func main() {
	ctx := context.Background()

	dev, err := linux.NewDevice()
	if err != nil {
		fmt.Println("default device not found:", err)
		return
	}
	ble.SetDefaultDevice(dev)

	cam, err := Connect(ctx)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("DETECTED: %#v\n", cam.DeviceInformation)

	quit := make(chan os.Signal)
	signal.Notify(quit, os.Interrupt, syscall.SIGTERM)
	quitting := false

	for {
		select {
		case <-time.After(time.Second / 10):
			if !quitting {
				fmt.Printf("\rCONN %s [%s] / TX %d / RSSI %d", CamName, cam.Addr(), cam.TxPower, cam.ReadRSSI())
			}
		case <-quit:
			fmt.Println()
			fmt.Print("Ctrl+C, closing connection: ")
			if err := cam.CancelConnection(); err != nil {
				fmt.Print("failed:", err)
				return
			}
			fmt.Print("ok")
			quitting = true
		case <-cam.Disconnected():
			fmt.Println()
			fmt.Println("Disconnected.")
			return
		}
	}
}
