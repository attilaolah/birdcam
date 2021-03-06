package elf

// #include <elf.h>
import "C"

import "unsafe"

var Class32 class = C.ELFCLASS32

type ELF32 interface {
	Header32() *C.Elf32_Ehdr
}

func (e *elf) Header32() *C.Elf32_Ehdr {
	return (*C.Elf32_Ehdr)(unsafe.Pointer(&e.data[0]))
}
