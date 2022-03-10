package elf

// #include <linux/elf.h>
import "C"

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

var (
	order map[uint8]binary.ByteOrder = map[uint8]binary.ByteOrder{
		C.ELFDATA2LSB: binary.LittleEndian,
		C.ELFDATA2MSB: binary.BigEndian,
	}

	Class32 class = C.ELFCLASS32
	Class64 class = C.ELFCLASS64

	ABINone  osabi = C.ELFOSABI_NONE
	ABILinux osabi = C.ELFOSABI_LINUX
)

type ELF interface {
	ELF32
	ELF64

	Data() []byte
}

type elf struct {
	data []byte
	cls  class
	abi  osabi
	bo   binary.ByteOrder
}

type class uint8
type osabi uint8

func Parse(data []byte) (ELF, error) {
	if l := len(data); l < C.EI_NIDENT {
		return nil, fmt.Errorf("wrong size: expected %d+ bytes of data, got: %d", C.EI_NIDENT, l)
	}
	if mag := data[C.EI_MAG0:C.SELFMAG]; bytes.Compare([]byte(C.ELFMAG), mag) != 0 {
		return nil, fmt.Errorf("wrong magic number: expected %q, got: %q", C.ELFMAG, mag)
	}

	cls := data[C.EI_CLASS]
	if cls <= C.ELFCLASSNONE || C.ELFCLASSNUM <= cls {
		return nil, fmt.Errorf("wrong class: expected (%d, %d), got: %d", C.ELFCLASSNONE, C.ELFCLASSNUM, cls)
	}

	bom := data[C.EI_DATA]
	bo, ok := order[bom]
	if !ok {
		return nil, fmt.Errorf("wronge byte order mark: %d", bom)
	}

	if v := data[C.EI_VERSION]; v <= C.EV_NONE || C.EV_NUM <= v {
		return nil, fmt.Errorf("wrong version: %d", v)
	}

	return &elf{
		data: data,
		cls:  class(cls),
		abi:  osabi(data[C.EI_OSABI]),
		bo:   bo,
	}, nil
}

func (e *elf) Data() []byte {
	return e.data
}
