package coolpix

import (
	"encoding/binary"
	"encoding/json"
	"fmt"
	"strings"

	ls_sec "github.com/attilaolah/birdcam/nikon"
)

// EncryptMode describes WiFi encryption modes supported by COOLPIX cameras.
type EncryptMode uint8

// WiFi encryption modes supported by COOLPIX cameras.
const (
	Open EncryptMode = iota
	WPA2
	WPA3
	WPA2WPA3
	EncryptModeUnknown
)

// ConnectionConfigurationData holds Bluetooth and WiFi connection configuration.
type ConnectionConfigurationData struct {
	WiFi      *WiFiConfigurationData      `json:"wifi,omitempty"`
	Bluetooth *BluetoothConfigurationData `json:"bluetooth,omitempty"`
}

type WiFiConfigurationData struct {
	SSID     string      `json:"ssid,omitempty"`
	Password string      `json:"password,omitempty"`
	Security EncryptMode `json:"security"`
}

type BluetoothConfigurationData struct {
	SPPMaxDataLength uint32 `json:"spp_max_data_length"`
}

func (m EncryptMode) MarshalJSON() ([]byte, error) {
	return json.Marshal(map[EncryptMode]string{
		Open:     "OPEN",
		WPA2:     "WPA2",
		WPA3:     "WPA2",
		WPA2WPA3: "WPA2|WPA3",
	}[m])

}

// DecodeConnectionConfiguration decodes and decrypts connection configuration data.
func DecodeConnectionConfiguration(ls ls_sec.Decoder, data []byte) (*ConnectionConfigurationData, error) {
	if len(data) == 0 {
		return nil, fmt.Errorf("failed to decode connection confiugariton: %w", ErrNoData)
	}

	c := ConnectionConfigurationData{}
	if data[0]&1 == 1 {
		c.WiFi = &WiFiConfigurationData{}
	}
	if (data[0]>>1)&1 == 1 {
		c.Bluetooth = &BluetoothConfigurationData{}
	}
	data = data[1:]

	if c.WiFi != nil {
		size := 32
		if l := len(data); l < size {
			return nil, fmt.Errorf("failed to decode wifi ssid: expected %d bytes, found: %d", size, l)
		}
		if buf, err := ls.Decode(data[:size]); err != nil {
			return nil, fmt.Errorf("failed to decode wifi ssid: %w", err)
		} else {
			c.WiFi.SSID = strings.Trim(string(buf), "\x00")
		}
		data = data[size:]

		size = 64
		if l := len(data); l < size {
			return nil, fmt.Errorf("failed to decode wifi password: expected %d bytes, found: %d", size, l)
		}
		if buf, err := ls.Decode(data[:size]); err != nil {
			return nil, fmt.Errorf("failed to decode wifi password: %w", err)
		} else {
			c.WiFi.Password = strings.Trim(string(buf), "\x00")
		}
		data = data[size:]

		if len(data) == 0 {
			return nil, fmt.Errorf("failed to decode wifi security: %w", ErrNoData)
		}
		c.WiFi.Security = EncryptMode(data[0])
		if c.WiFi.Security >= EncryptModeUnknown {
			return nil, fmt.Errorf("unknown encrypt mode: %d", c.WiFi)
		}
		data = data[1:]
	}

	if c.Bluetooth != nil {
		size := 4
		if l := len(data); l < size {
			return nil, fmt.Errorf("failed to decode bluetooth ssp max data length: expected %d bytes, found: %d", size, l)
		}
		c.Bluetooth.SPPMaxDataLength = binary.LittleEndian.Uint32(data)
		data = data[size:]
	}

	return &c, nil
}
