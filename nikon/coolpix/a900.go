package coolpix

import (
	"context"
	"encoding/binary"
	"errors"
	"fmt"
	"math/rand"
	"strings"
	"time"

	"github.com/go-ble/ble"
	"tinygo.org/x/bluetooth"

	ls_sec "github.com/attilaolah/birdcam/nikon"
)

// LocalName advertised by this camera model.
const A900ModelName = "A900"

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

type A900 struct {
	ble.Client

	TxPower int
}

var (
	ErrCharNotFound        = errors.New("characteristic not found")
	ErrCharNotReadable     = errors.New("characteristic does not support reading")
	ErrCharNotWritable     = errors.New("characteristic does not support writing")
	ErrCharNotNotifyable   = errors.New("characteristic does not support notification")
	ErrCharNotIndicateable = errors.New("characteristic does not support indication")
	ErrDisconnected        = errors.New("disconnected from camera")
)

// Connect connects to the camera.
func Connect(ctx context.Context) (cam *A900, err error) {
	var txp int
	cli, err := ble.Connect(ctx, func(a ble.Advertisement) bool {
		if a.LocalName() != A900ModelName || !a.Connectable() {
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

// SetMaxMTU sets the MTU to the maximum allowed value.
func (cam *A900) SetMaxMTU() error {
	_, err := cam.ExchangeMTU(ble.MaxMTU)
	return err
}

// Authenticate authenticates with the camera.
func (cam *A900) Authenticate() error {
	var err error
	var auth <-chan []byte
	if auth, err = cam.Indicate(Authentication); err != nil {
		return fmt.Errorf("auth error: failed to indicate authentication: %w", err)
	}

	ls := ls_sec.New(rand.Uint32())
	defer ls.Free()

	// STAGE 1
	stage := ls_sec.Stage1
	stage1, err := ls.Stage1()
	if err != nil {
		return fmt.Errorf("auth error: stage_1: %w", err)
	}
	clientID := rand.Uint64()
	if err = cam.WriteBytes(Authentication, ls_sec.Pack(stage, stage1, clientID)); err != nil {
		return fmt.Errorf("auth error: writing stage_1: %w", err)
	}

	// STAGE 2
	var stage2, cameraID uint64
	select {
	case buf := <-auth:
		if stage, stage2, cameraID, err = ls_sec.Unpack(buf); err != nil {
			return fmt.Errorf("auth error: reading stage_2: %w", err)
		}
	case <-cam.Disconnected():
		return fmt.Errorf("auth error: reading stage_2: %w", ErrDisconnected)
	}
	if stage != ls_sec.Stage2 {
		return fmt.Errorf("auth error: expected stage %d, got: %d", ls_sec.Stage2, stage)
	}

	// STAGE 3
	stage = ls_sec.Stage3
	stage3, err := ls.Stage3(stage2, stage1, cameraID)
	if err != nil {
		return fmt.Errorf("auth error: stage_3: %w", err)
	}
	if err = cam.WriteBytes(Authentication, ls_sec.Pack(stage, stage1, stage3)); err != nil {
		return fmt.Errorf("auth error: writing stage_3: %w", err)
	}

	// STAGE 4
	var stage4 uint64
	select {
	case buf := <-auth:
		if stage, _, stage4, err = ls_sec.Unpack(buf); err != nil {
			return fmt.Errorf("auth error: reading stage_4: %w", err)
		}
	case <-cam.Disconnected():
		return fmt.Errorf("auth error: reading stage_4: %w", ErrDisconnected)
	}
	if stage != ls_sec.Stage4 {
		return fmt.Errorf("auth error: expected stage %d, got: %d", ls_sec.Stage4, stage)
	}

	// TODO: Unsubscribe from auth indications!

	// TODO: Store Stage 4 value!
	_ = stage4

	return nil
}

// Notify subscribes for notifications on a characteristic.
// The returned channel should be read continuously to avoid deadlocks.
func (cam *A900) Notify(c *ble.Characteristic) (<-chan []byte, error) {
	return cam.subscribe(c, false)
}

// Indicate subscribes for indications on a characteristic.
// The returned channel should be read continuously to avoid deadlocks.
func (cam *A900) Indicate(c *ble.Characteristic) (<-chan []byte, error) {
	return cam.subscribe(c, true)
}

// Subscribe for notifications or indications on a characteristic.
// The returned channel should be read continuously to avoid deadlocks.
func (cam *A900) subscribe(c *ble.Characteristic, indicate bool) (<-chan []byte, error) {
	p, err := cam.profile()
	if err != nil {
		return nil, err
	}

	ch := make(chan []byte)

	if c = p.FindCharacteristic(c); c == nil {
		return nil, ErrCharNotFound
	}
	if indicate && c.Property|ble.CharIndicate == 0 {
		return nil, ErrCharNotIndicateable
	} else if !indicate && c.Property|ble.CharNotify == 0 {
		return nil, ErrCharNotNotifyable
	}

	if err = cam.Subscribe(c, indicate, func(req []byte) {
		ch <- req
	}); err != nil {
		return nil, fmt.Errorf("failed to subscribe: %w", err)
	}

	return ch, nil
}

func (cam *A900) SetWiFi(on bool) error {
	buf := []byte{0}
	if on {
		buf[0] = 1
	}
	return cam.WriteBytes(ConnectionEstablishment, buf)
}

func (cam *A900) ManufacturerName() (string, error) {
	return cam.ReadString(ManufacturerNameString)
}

func (cam *A900) ModelNumber() (string, error) {
	return cam.ReadString(ModelNumberString)
}

func (cam *A900) SoftwareRevision() (string, error) {
	return cam.ReadString(SoftwareRevisionString)
}

func (cam *A900) FirmwareRevision() (string, error) {
	return cam.ReadString(FirmwareRevisionString)
}

func (cam *A900) LSSSerialNumber() (string, error) {
	return cam.ReadString(LSSSerialNumberString)
}

func (cam *A900) ServerDeviceName() (string, error) {
	return cam.ReadString(ServerDeviceName)
}

// Return the battery level, as a % between 0 and 100.
func (cam *A900) BatteryLevel() (uint8, error) {
	buf, err := cam.ReadBytes(BatteryLevel)
	if err != nil {
		return 0, err
	}
	if len(buf) != 1 {
		return 0, fmt.Errorf("battery_level: expected 1 byte, got %d: %#v", len(buf), buf)
	}

	return buf[0], nil
}

// WriteCurrentTime writes the current time to the camera.
func (cam *A900) WriteCurrentTime() error {
	t := time.Now()
	u := t.UTC()
	_, offset := t.Zone()

	// YYMDHMS?ZZ
	buf := make([]byte, 10)
	binary.LittleEndian.PutUint16(buf, uint16(u.Year()))
	buf[2] = uint8(u.Month())
	buf[3] = uint8(u.Day())
	buf[4] = uint8(u.Hour())
	buf[5] = uint8(u.Minute())
	buf[6] = uint8(u.Second())
	// Byte 7 is left at zero value.
	buf[8] = uint8(time.Duration(offset) * time.Second / time.Hour)
	// This is a guess: the last byte may indicate a non-integer hour time zone offset.
	buf[9] = uint8((time.Duration(offset) * time.Second / time.Minute) % (time.Hour / time.Minute))

	return cam.WriteBytes(CurrentTime, buf)
}

// Read a characteristic as a raw byte slice.
func (cam *A900) ReadBytes(c *ble.Characteristic) ([]byte, error) {
	p, err := cam.profile()
	if err != nil {
		return nil, err
	}

	if c = p.FindCharacteristic(c); c == nil {
		return nil, ErrCharNotFound
	}
	if c.Property|ble.CharRead == 0 {
		return nil, ErrCharNotReadable
	}
	buf, err := cam.ReadCharacteristic(c)
	if err != nil {
		return nil, fmt.Errorf("failed to read characteristic: %w", err)
	}

	return buf, nil
}

// Write a raw byte slice to a characteristic handle.
func (cam *A900) WriteBytes(c *ble.Characteristic, buf []byte) error {
	p, err := cam.profile()
	if err != nil {
		return err
	}

	if c = p.FindCharacteristic(c); c == nil {
		return ErrCharNotFound
	}
	if c.Property|ble.CharWrite == 0 {
		return ErrCharNotWritable
	}
	return cam.WriteCharacteristic(c, buf, false)
}

// ReadString reads a characteristic as a zero-padded string.
func (cam *A900) ReadString(c *ble.Characteristic) (string, error) {
	buf, err := cam.ReadBytes(c)
	if err != nil {
		return "", err
	}
	return strings.Trim(string(buf), "\x00"), nil
}

// WriteString writes zero-padded string to a characteristic handle.
func (cam *A900) WriteString(c *ble.Characteristic, s string, pad int) error {
	buf := make([]byte, pad)
	copy(buf, s)
	return cam.WriteBytes(c, buf)
}

// ModelName returns the model name.
func (cam *A900) ModelName() string {
	return A900ModelName
}

// Discover the camera profile if needed.
func (cam *A900) profile() (*ble.Profile, error) {
	if p := cam.Profile(); p != nil {
		return p, nil
	}

	p, err := cam.DiscoverProfile(false)
	if err != nil {
		return nil, fmt.Errorf("failed to discover profile: %w", err)
	}
	return p, nil
}
