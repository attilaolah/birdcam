package ls_sec

// #include "nikon/ls_sec/cgo.h"
import "C"
import (
	"encoding/binary"
	"fmt"
	"unsafe"
)

const (
	OK      = 0
	BufSize = 17
)

const (
	Stage1 uint8 = 1 + iota
	Stage2
	Stage3
	Stage4
	Stage5
)

type LsSec struct {
	ls_sec C.LsSec
}

type Error int8

var (
	ErrAlign Error
	ErrAuthn Error
	ErrStage Error
)

func init() {
	ErrAlign = Error(C.ls_sec_err_align)
	ErrAuthn = Error(C.ls_sec_err_authn)
	ErrStage = Error(C.ls_sec_err_stage)
}

func (err Error) Error() string {
	return C.GoString(C.ls_sec_error(C.int8_t(err)))
}

func New(seed uint32) *LsSec {
	return &LsSec{
		ls_sec: C.ls_sec_new(C.uint32_t(seed)),
	}
}

func (ls *LsSec) Free() {
	C.ls_sec_free(ls.ls_sec)
}

func (ls *LsSec) Stage1() (uint64, error) {
	var dst C.uint64_t
	status := C.ls_sec_stage_1(ls.ls_sec, &dst)
	if status != OK {
		return 0, Error(status)
	}
	return uint64(dst), nil
}

func (ls *LsSec) Stage2(stage_1 uint64) (uint64, uint64, error) {
	var dst_1, dst_2 C.uint64_t
	status := C.ls_sec_stage_2(ls.ls_sec, C.uint64_t(stage_1), &dst_1, &dst_2)
	if status != OK {
		return 0, 0, Error(status)
	}
	return uint64(dst_1), uint64(dst_2), nil
}

func (ls *LsSec) Stage3(nonce, stage_1, device_id uint64) (uint64, error) {
	var dst C.uint64_t
	status := C.ls_sec_stage_3(ls.ls_sec, C.uint64_t(nonce), C.uint64_t(stage_1), C.uint64_t(device_id), &dst)
	if status != OK {
		return 0, Error(status)
	}
	return uint64(dst), nil
}

func (ls *LsSec) Stage4(nonce, stage_1, stage_3 uint64) error {
	if status := C.ls_sec_stage_4(ls.ls_sec, C.uint64_t(nonce), C.uint64_t(stage_1), C.uint64_t(stage_3)); status != OK {
		return Error(status)
	}
	return nil
}

func (ls *LsSec) GenerateKey(stage_4, device_id uint64) error {
	if status := C.ls_sec_generate_key(ls.ls_sec, C.uint64_t(stage_4), C.uint64_t(device_id)); status != OK {
		return Error(status)
	}
	return nil
}

// Encode implements the Encoder interface.
func (ls *LsSec) Encode(data []byte) ([]byte, error) {
	result := make([]byte, len(data))
	if status := C.ls_sec_encode(ls.ls_sec, (*C.uint8_t)(unsafe.Pointer(&data[0])), (*C.uint8_t)(unsafe.Pointer(&result[0])), C.size_t(len(data))); status != OK {
		return nil, Error(status)
	}
	return result, nil
}

// Decoder implements the Decored interface.
func (ls *LsSec) Decode(data []byte) ([]byte, error) {
	result := make([]byte, len(data))
	if status := C.ls_sec_decode(ls.ls_sec, (*C.uint8_t)(unsafe.Pointer(&data[0])), (*C.uint8_t)(unsafe.Pointer(&result[0])), C.size_t(len(data))); status != OK {
		return nil, Error(status)
	}
	return result, nil
}

// Pack the 17-byte auth buffer.
func Pack(stage uint8, buf1, buf2 uint64) []byte {
	buf := make([]byte, BufSize)
	buf[0] = stage
	binary.LittleEndian.PutUint64(buf[1:], buf1)
	binary.LittleEndian.PutUint64(buf[9:], buf2)
	return buf
}

// Unpack the 17-byte auth buffer.
func Unpack(buf []byte) (uint8, uint64, uint64, error) {
	if len(buf) != BufSize {
		return 0, 0, 0, fmt.Errorf("ls_sec: expected %d bytes, got %d: %#v", BufSize, len(buf), buf)
	}
	return buf[0], binary.LittleEndian.Uint64(buf[1:]), binary.LittleEndian.Uint64(buf[9:]), nil
}

// Encoder interface to use for encoding only.
type Encoder interface {
	Encode(data []byte) ([]byte, error)
}

// Decoder interface to use for decoding only.
type Decoder interface {
	Decode(data []byte) ([]byte, error)
}

// LsSec implements both these interfaces.
var (
	_ Encoder = &LsSec{}
	_ Decoder = &LsSec{}
)
