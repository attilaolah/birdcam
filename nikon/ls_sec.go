package main

// #include "nikon/ls_sec_cgo.h"
import "C"

import (
	"fmt"
)

type LsSec struct {
	ls_sec C.LsSec
}

func New(seed uint32) *LsSec {
	return &LsSec{
		ls_sec: C.ls_sec_new(C.uint32_t(seed)),
	}
}

func (ls *LsSec) Free() {
	C.ls_sec_free(ls.ls_sec)
}

func (ls *LsSec) Stage1() uint64 {
	return uint64(C.ls_sec_stage_1(ls.ls_sec))
}

func main() {
	ls := New(1)
	defer ls.Free()

	fmt.Println("exp:", 7749363893351949254, "got:", ls.Stage1())
}
