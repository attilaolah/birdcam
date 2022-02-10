# Nikon Coolpix A900

Build `scan.go` to scan for and connect to Nikon Coolpix A900 devices via
Bluetooth LE.

```sh
$ go build scan.go
$ sudo setcap 'cap_net_raw,cap_net_admin=eip' scan
$ ./scan
```

## TODO

The next step would be to pair (authenticate) with the camera so that we can
enable the WiFi.

There is an Android app called "SnapBridge" that can do it, by writing `0x01`
to the Bluetooth characteristic with UUID
`00002005-3DD4-4255-8D62-6DC7B9BD5561`, however, before we can do that, the
devices need to be "paired".

This is done using a 3-way handshake to the characteristic with UUID
`00002000-3DD4-4255-8D62-6DC7B9BD5561`.

Example successful 3-way handshakes, performed by the app:

---

- Phone -> Camera: `01 480a18d127efee4 28457d5704c2be553`
- Camera -> Phone: `02 000062630000676 4357ed673c4281573`
- Phone -> Camera: `03 480a18d127efee4 2988f74040e99ffc2`

---

- Phone -> Camera: `01 0bb2f119679250af 8457d5704c2be553`
- Camera -> Phone: `02 000061730000589e cedf128b01214348`
- Phone -> Camera: `03 0bb2f119679250af c5daf56728f5c358`

---
