package elf

// #include <elf.h>
import "C"

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

var (
	ABINone  osabi = C.ELFOSABI_NONE
	ABILinux osabi = C.ELFOSABI_LINUX
)

// ELF is the main public interface.
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

// Parse wraps a byte slice for direct access.
func Parse(data []byte) (ELF, error) {
	if l := len(data); l < C.EI_NIDENT {
		return nil, fmt.Errorf("wrong size: expected %d+ bytes of data, got: %d", C.EI_NIDENT, l)
	}
	if mag := data[:C.SELFMAG]; bytes.Compare([]byte(C.ELFMAG), mag) != 0 {
		return nil, fmt.Errorf("wrong magic number: expected %q, got: %q", C.ELFMAG, mag)
	}

	cls := data[C.EI_CLASS]
	if cls <= C.ELFCLASSNONE || C.ELFCLASSNUM <= cls {
		return nil, fmt.Errorf("wrong class: expected (%d, %d), got: %d", C.ELFCLASSNONE, C.ELFCLASSNUM, cls)
	}

	bom := data[C.EI_DATA]
	if bom <= C.ELFDATANONE || C.ELFDATANUM <= bom {
		return nil, fmt.Errorf("wrong byte order mark: expected (%d, %d), got: %d", C.ELFDATANONE, C.ELFDATANUM, bom)
	}

	if v := data[C.EI_VERSION]; v != C.EV_CURRENT {
		return nil, fmt.Errorf("wrong version: expected %d, got: %d", C.EV_CURRENT, v)
	}

	return &elf{
		data: data,
		cls:  class(cls),
		abi:  osabi(data[C.EI_OSABI]),
		bo: map[uint8]binary.ByteOrder{
			C.ELFDATA2LSB: binary.LittleEndian,
			C.ELFDATA2MSB: binary.BigEndian,
		}[bom],
	}, nil
}

// Data provides direct access to the underlying bytes.
func (e *elf) Data() []byte {
	return e.data
}
