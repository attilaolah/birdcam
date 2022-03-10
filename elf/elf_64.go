package elf

// #include <linux/elf.h>
import "C"

import "unsafe"

type ELF64 interface {
	// Header
	Header64() *C.Elf64_Ehdr

	// Program header table
	PHT64() []*C.Elf64_Phdr

	// Section header table
	// TODO!

	// Sections
	PTDynamic64() []*C.Elf64_Dyn

	// Tables
	StrTab64() []string

	// Mutators
	PatchStr64(string, string) error
	RmDtNeeded64(string) error
}

func (e *elf) Header64() *C.Elf64_Ehdr {
	return (*C.Elf64_Ehdr)(unsafe.Pointer(&e.data[0]))
}
