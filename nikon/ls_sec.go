package ls_sec

// #include "nikon/ls_sec_cgo.h"
import "C"

import (
	"fmt"
)

const OK = 0

type LsSec struct {
	ls_sec C.LsSec
}

type Error int8

var (
	ErrAuth       Error = -102
	ErrWrongStage Error = -103
)

func (err Error) Error() string {
	// TODO: Pull error codes from cgo!
	return fmt.Sprintf("ls_sec error: %d", int8(err))
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
