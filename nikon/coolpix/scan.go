package coolpix

import (
	"context"
	"encoding/binary"
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/go-ble/ble"
	"github.com/go-ble/ble/linux"
)

func Main() {
	ctx := context.Background()

	fmt.Print("Searching for Bluetooth device: ")
	dev, err := linux.NewDevice()
	if err != nil {
		fmt.Println("default device not found:", err)
		return
	}
	ble.SetDefaultDevice(dev)
	fmt.Println("OK!")

	fmt.Print("Connecting: ")
	cam, err := Connect(ctx)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("OK!")

	fmt.Print("Authenticating: ")
	if err = cam.Authenticate(); err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println("OK!")

	if b, err := cam.BatteryLevel(); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("battery_level:", b)
	}

	buf := make([]byte, 32)
	copy(buf, "Android_Pixel_5_5797")
	fmt.Println("writing client_device_name")
	if err = cam.WriteBytes(ClientDeviceName, buf); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("ok!")
	}

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
	if err = cam.WriteBytes(CurrentTime, buf); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("ok!")
	}

	fmt.Println("reading connection_configuration")
	if buf, err := cam.ReadBytes(ConnectionConfiguration); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("ok! connection_configuration:", buf)
	}

	fmt.Println("writing connection_establishment")
	if err := cam.WriteBytes(ConnectionEstablishment, []byte{1}); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("ok!")
	}

	quit := make(chan os.Signal)
	signal.Notify(quit, os.Interrupt, syscall.SIGTERM)
	quitting := false

	for {
		select {
		case <-time.After(time.Second / 10):
			if !quitting {
				fmt.Printf("\rCONN %s [%s] / TX %d / RSSI %d", A900ModelName, cam.Addr(), cam.TxPower, cam.ReadRSSI())
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
