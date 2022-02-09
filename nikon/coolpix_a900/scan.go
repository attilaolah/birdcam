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

var (
	// Standard BLE characteristics.
	// These are available in https://pkg.go.dev/tinygo.org/x/bluetooth.
	ManufacturerNameString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDManufacturerNameString.Get16Bit()))
	ModelNumberString      = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDModelNumberString.Get16Bit()))
	SoftwareRevisionString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDSoftwareRevisionString.Get16Bit()))
	FirmwareRevisionString = ble.NewCharacteristic(ble.UUID16(bluetooth.CharacteristicUUIDFirmwareRevisionString.Get16Bit()))

	// COOLPIX A900 vendor-specific stuff.
	// These are mostly reverse-engineered, so take them with a grain of salt.

	// Service advertised by this camera model.
	Vendor = ble.NewService(ble.MustParse("0000de00-3dd4-4255-8d62-6dc7b9bd5561"))

	// Characteristics advertised by this camera model.
	SerialNumberString     = ble.NewCharacteristic(ble.MustParse("0000200b-3dd4-4255-8d62-6dc7b9bd5561"))
	DeviceIdentifierString = ble.NewCharacteristic(ble.MustParse("00002003-3dd4-4255-8d62-6dc7b9bd5561"))
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
			if Vendor.UUID.Equal(s) {
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
	if info.SerialNumber, err = ReadCharacteristic(cli, SerialNumberString); err != nil {
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
