package main

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"math/rand"
	"os"
	"os/signal"
	"strings"
	"syscall"
	"time"

	"github.com/go-ble/ble"
	"github.com/go-ble/ble/linux"
	"tinygo.org/x/bluetooth"

	ls_sec "github.com/attilaolah/birdcam/nikon"
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
	// Disassembled from SnapBridge APK / com/nikon/snapbridge/cmru/bleclient/services/lss/BleLssService.
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
	LSSSerialNumberString   = ble.NewCharacteristic(UUID(0x200b)) // 0x59 0x5a

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

	return &A900{
		Client:  cli,
		TxPower: txp,
	}, nil
}

func (cam *A900) DeviceInformation() (*DeviceInformation, error) {
	var err error
	info := DeviceInformation{}
	if info.ManufacturerName, err = cam.ReadString(ManufacturerNameString); err != nil {
		return nil, fmt.Errorf("failed to read manufacturer name: %w", err)
	}
	if info.ModelNumber, err = cam.ReadString(ModelNumberString); err != nil {
		return nil, fmt.Errorf("failed to read model number: %w", err)
	}
	if info.SoftwareRevision, err = cam.ReadString(SoftwareRevisionString); err != nil {
		return nil, fmt.Errorf("failed to read software revision: %w", err)
	}
	if info.FirmwareRevision, err = cam.ReadString(FirmwareRevisionString); err != nil {
		return nil, fmt.Errorf("failed to read firmware revision: %w", err)
	}
	if info.SerialNumber, err = cam.ReadString(LSSSerialNumberString); err != nil {
		return nil, fmt.Errorf("failed to read serial number: %w", err)
	}

	return &info, nil
}

func (cam *A900) ReadString(c *ble.Characteristic) (string, error) {
	p := cam.Profile()
	if p == nil {
		var err error
		if p, err = cam.DiscoverProfile(false); err != nil {
			return "", fmt.Errorf("failed to discover profile: %w", err)
		}
	}

	if c := p.FindCharacteristic(c); c == nil {
		return "", errors.New("characteristic not found")
	} else if c.Property|ble.CharRead == 0 {
		return "", errors.New("characteristic cannot be read")
	} else {
		if buf, err := cam.ReadCharacteristic(c); err != nil {
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

	fmt.Println("Connected.")
	//fmt.Println("Connected, fetching device info.")
	//if info, err := cam.DeviceInformation(); err == nil {
	//	fmt.Printf("Device Info: %#v\n", info)
	//} else {
	//	fmt.Println("error getting device information:", err)
	//}
	p := cam.Profile()
	if p == nil {
		if p, err = cam.DiscoverProfile(false); err != nil {
			fmt.Println("failed to discover profile:", err)
			return
		}
	}

	quit := make(chan os.Signal)
	signal.Notify(quit, os.Interrupt, syscall.SIGTERM)
	quitting := false

	fmt.Printf("Notification-Subscribing @ %s: ", LSSControlPoint.UUID)
	if c := p.FindCharacteristic(LSSControlPoint); c == nil {
		fmt.Println("characteristic not found!")
	} else {
		if c.Property|ble.CharNotify == 0 {
			fmt.Println("characteristic does not support notification!")
		}
		if err = cam.Subscribe(c, false, func(req []byte) {
			fmt.Println("NOT: %s = %#v", LSSControlPoint.UUID, req)
		}); err != nil {
			fmt.Println("error:", err)
		} else {
			fmt.Println("ok!")
		}
	}

	ls := ls_sec.New(rand.Uint32())
	defer ls.Free()

	nonce, err := ls.Stage1()
	if err != nil {
		fmt.Println("stage_1 error:", err)
		return
	}
	devID := rand.Uint64()

	fmt.Printf("Indication-Subscribing @ %s: ", Authentication.UUID)
	if c := p.FindCharacteristic(Authentication); c == nil {
		fmt.Println("characteristic not found!")
	} else {
		if c.Property|ble.CharIndicate == 0 {
			fmt.Println("characteristic does not support indication!")
		}
		if err = cam.Subscribe(c, true, func(req []byte) {
			fmt.Printf("IND: %s = %#v\n", Authentication.UUID, req)
			if len(req) != 17 {
				fmt.Println("request length != 17:", len(req))
				return
			}
			if req[0] == 2 {
				fmt.Println("response: stage 2")
				camNonce := binary.LittleEndian.Uint64(req[1:])
				camDevID := binary.LittleEndian.Uint64(req[9:])
				fmt.Printf("received nonce = %d, dev_id = %d\n", camNonce, camDevID)

				stage_3, err := ls.Stage3(camNonce, nonce, camDevID)
				if err != nil {
					fmt.Println("stage_3 error:", err)
				}
				fmt.Println("stage_3:", stage_3)

				buf := make([]byte, 17)
				buf[0] = 0x03 // stage_3
				binary.LittleEndian.PutUint64(buf[1:], nonce)
				binary.LittleEndian.PutUint64(buf[9:], stage_3)
				fmt.Printf("sending nonce = %d, stage_3 = %d\n", nonce, stage_3)

				go func() {
					if c := p.FindCharacteristic(Authentication); c == nil {
						fmt.Println("characteristic not found!")
					} else {
						if c.Property|ble.CharWrite == 0 {
							fmt.Println("characteristic does not support writing!")
						}
						if err := cam.WriteCharacteristic(c, buf, false); err != nil {
							fmt.Println("error:", err)
						} else {
							fmt.Println("\nok!")
						}
					}
				}()
				return
			}
			if req[0] == 4 {
				fmt.Println("stage_4:", binary.LittleEndian.Uint64(req[9:]))

				go func() {
					fmt.Println("reading battery_level")
					if c := p.FindCharacteristic(BatteryLevel); c == nil {
						fmt.Println("characteristic not found!")
					} else if c.Property|ble.CharRead == 0 {
						fmt.Println("characteristic does not support reading!")
					} else {
						if buf, err := cam.ReadCharacteristic(c); err != nil {
							fmt.Println("error:", err)
						} else if len(buf) != 1 {
							fmt.Printf("error: battery_level: got %d bytes: %#v\n", len(buf), buf)
						} else {
							fmt.Println("\nok! battery_level [%]:", buf[0])
						}
					}
					time.Sleep(time.Second)

					fmt.Println("writing client_device_name")

					buf := make([]byte, 32)
					copy(buf, "Android_Pixel_5_5797")
					if c := p.FindCharacteristic(ClientDeviceName); c == nil {
						fmt.Println("characteristic not found!")
					} else {
						if c.Property|ble.CharWrite == 0 {
							fmt.Println("characteristic does not support writing!")
						}
						if err := cam.WriteCharacteristic(c, buf, false); err != nil {
							fmt.Println("error:", err)
						} else {
							fmt.Println("ok!")
						}
					}
					time.Sleep(time.Second)

					/*
						fmt.Println("reading server_device_name")
						if c := p.FindCharacteristic(ServerDeviceName); c == nil {
							fmt.Println("characteristic not found!")
						} else if c.Property|ble.CharRead == 0 {
							fmt.Println("characteristic does not support reading!")
						} else {
							if buf, err := cam.ReadCharacteristic(c); err != nil {
								fmt.Println("error:", err)
							} else {
								fmt.Println("\nok! server_device_name:", strings.TrimSpace(strings.Trim(string(buf), "\x00")))
							}
						}
						time.Sleep(time.Second)
					*/

					buf = make([]byte, 10)
					now := time.Now()
					utc := now.UTC()
					_, offset := now.Zone()
					binary.LittleEndian.PutUint16(buf, uint16(utc.Year()))
					buf[2] = uint8(utc.Month())
					buf[3] = uint8(utc.Day())
					buf[4] = uint8(utc.Hour())
					buf[5] = uint8(utc.Minute())
					buf[6] = uint8(utc.Second())
					buf[8] = uint8(time.Duration(offset) * time.Second / time.Hour)
					buf[9] = uint8((time.Duration(offset) * time.Second / time.Minute) % (time.Hour / time.Minute))

					fmt.Println("writing current_time:", now, "encoded:", buf)
					if c := p.FindCharacteristic(CurrentTime); c == nil {
						fmt.Println("characteristic not found!")
					} else {
						if c.Property|ble.CharWrite == 0 {
							fmt.Println("characteristic does not support writing!")
						}
						if err := cam.WriteCharacteristic(c, buf, false); err != nil {
							fmt.Println("error:", err)
						} else {
							fmt.Println("ok!")
						}
					}
					time.Sleep(time.Second)

					/*
						fmt.Println("reading lss_feature")
						if c := p.FindCharacteristic(LSSFeature); c == nil {
							fmt.Println("characteristic not found!")
						} else if c.Property|ble.CharRead == 0 {
							fmt.Println("characteristic does not support reading!")
						} else {
							if buf, err := cam.ReadCharacteristic(c); err != nil {
								fmt.Println("error:", err)
							} else {
								fmt.Println("\nok! lss_feature:", buf)
							}
						}
						time.Sleep(time.Second)

						fmt.Println("reading manufacturer_name_string")
						if s, err := cam.ReadString(ManufacturerNameString); err != nil {
							fmt.Println("failed to read manufacturer name:", err)
						} else {
							fmt.Println("manufacturer_name_string:", s)
						}
						time.Sleep(time.Second)

						fmt.Println("reading lss_serial_number_string")
						if s, err := cam.ReadString(LSSSerialNumberString); err != nil {
							fmt.Println("failed to read serial number:", err)
						} else {
							fmt.Println("lss_serial_number_string:", s)
						}
						time.Sleep(time.Second)

						fmt.Println("reading firmware_revision_string")
						if s, err := cam.ReadString(FirmwareRevisionString); err != nil {
							fmt.Println("failed to read serial number:", err)
						} else {
							fmt.Println("firmware_revision_string:", s)
						}
						time.Sleep(time.Second)

						for i := 0; i < 3; i++ {
							fmt.Println("reading lss_feature")
							if c := p.FindCharacteristic(LSSFeature); c == nil {
								fmt.Println("characteristic not found!")
							} else if c.Property|ble.CharRead == 0 {
								fmt.Println("characteristic does not support reading!")
							} else {
								if buf, err := cam.ReadCharacteristic(c); err != nil {
									fmt.Println("error:", err)
								} else {
									fmt.Println("\nok! lss_feature:", buf)
								}
							}
							time.Sleep(time.Second)
						}

						fmt.Println("fetching device info")
						if info, err := cam.DeviceInformation(); err == nil {
							fmt.Printf("Device Info: %#v\n", info)
						} else {
							fmt.Println("error getting device information:", err)
						}
					*/

					fmt.Println("reading connection_configuration")
					if c := p.FindCharacteristic(ConnectionConfiguration); c == nil {
						fmt.Println("characteristic not found!")
					} else if c.Property|ble.CharRead == 0 {
						fmt.Println("characteristic does not support reading!")
					} else {
						if buf, err := cam.ReadCharacteristic(c); err != nil {
							fmt.Println("error:", err)
						} else {
							fmt.Println("\nok! connection_configuration:", buf)
						}
					}
					time.Sleep(time.Second)

					fmt.Println("writing connection_establishment")
					if c := p.FindCharacteristic(ConnectionEstablishment); c == nil {
						fmt.Println("characteristic not found!")
					} else {
						if c.Property|ble.CharWrite == 0 {
							fmt.Println("characteristic does not support writing!")
						}
						if err := cam.WriteCharacteristic(c, []byte{0x01}, false); err != nil {
							fmt.Println("error:", err)
						} else {
							fmt.Println("\nok!")
						}
					}

				}()
				return
			}
			fmt.Println("received unexpected stage:", req[0])
		}); err != nil {
			fmt.Println("error:", err)
		} else {
			fmt.Println("ok!")
		}
	}

	fmt.Printf("Authenticating: ")

	buf := make([]byte, 17)
	buf[0] = 0x01 // stage_1
	binary.LittleEndian.PutUint64(buf[1:], nonce)
	binary.LittleEndian.PutUint64(buf[9:], devID)
	fmt.Printf("sending nonce = %d, dev_id = %d\n", nonce, devID)

	if c := p.FindCharacteristic(Authentication); c == nil {
		fmt.Println("characteristic not found!")
	} else {
		if c.Property|ble.CharWrite == 0 {
			fmt.Println("characteristic does not support writing!")
		}
		if err := cam.WriteCharacteristic(c, buf, false); err != nil {
			fmt.Println("error:", err)
		} else {
			fmt.Println("ok!")
		}
	}

	// Enabling Wi-Fi won't work until authentication is completed.

	//fmt.Printf("Enabling WiFi: ")
	//if c := p.FindCharacteristic(ConnectionEstablishment); c == nil {
	//	fmt.Println("characteristic not found!")
	//} else {
	//	if c.Property|ble.CharWrite == 0 {
	//		fmt.Println("characteristic does not support writing!")
	//	}
	//	if err := cam.WriteCharacteristic(c, []byte{0x01}, false); err != nil {
	//		fmt.Println("error:", err)
	//	} else {
	//		fmt.Println("ok!")
	//	}
	//}

	for {
		select {
		case <-time.After(time.Second / 10):
			if !quitting {
				fmt.Printf("\rCONN %s [%s] / TX %d / RSSI %d", CamName, cam.Addr(), cam.TxPower, cam.ReadRSSI())
			}
		case <-quit:
			quitting = true
			fmt.Println()
			fmt.Print("Ctrl+C, clearing subscriptions: ")
			if err := cam.ClearSubscriptions(); err != nil {
				fmt.Print("failed:", err)
				return
			}
			fmt.Print("ok; closing connection: ")
			if err := cam.CancelConnection(); err != nil {
				fmt.Print("failed:", err)
				return
			}
			fmt.Print("ok")
		case <-cam.Disconnected():
			fmt.Println()
			fmt.Println("Disconnected.")
			return
		}
	}
}
