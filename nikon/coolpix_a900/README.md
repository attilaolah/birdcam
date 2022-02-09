# Nikon Coolpix A900

Build `scan.go` to scan for and connect to Nikon Coolpix A900 devices via
Bluetooth LE.

```sh
$ go build scan.go
$ sudo setcap 'cap_net_raw,cap_net_admin=eip' scan
$ ./scan
```
