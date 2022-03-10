package elf

// #include <linux/elf.h>
import "C"

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"unsafe"
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

func (e *elf) PHT64() []*C.Elf64_Phdr {
	h := e.Header64()
	offset := int(h.e_phoff)
	size := int(h.e_phentsize)
	n := int(h.e_phnum)

	res := make([]*C.Elf64_Phdr, n)
	for i := 0; i < n; i++ {
		res[i] = (*C.Elf64_Phdr)(unsafe.Pointer(&e.data[(i*size)+offset]))
	}

	return res
}

func (e *elf) PTDynamic64() []*C.Elf64_Dyn {
	var p *C.Elf64_Phdr
	for _, ph := range e.PHT64() {
		if ph.p_type == C.PT_DYNAMIC {
			p = ph
			break
		}
	}
	if p == nil {
		return nil
	}

	res := []*C.Elf64_Dyn{}
	offset := int(p.p_offset)
	for {
		dyn := (*C.Elf64_Dyn)(unsafe.Pointer(&e.data[offset]))
		if dyn.d_tag == C.DT_NULL {
			break
		}
		res = append(res, dyn)
		offset += int(unsafe.Sizeof(C.Elf64_Dyn{}))
	}

	return res
}

func (e *elf) StrTab64() []string {
	offset, size := e.str64()

	pos := offset
	res := []string{}
	for pos < offset+size {
		if e.data[pos] == 0 {
			pos += 1
			continue
		}
		zero := bytes.IndexByte(e.data[pos:], 0x00)
		if zero == -1 {
			break
		}
		res = append(res, string(e.data[pos:pos+zero]))
		pos += zero
	}

	return res
}

// Update a string table entry.
func (e *elf) PatchStr64(from, to string) error {
	if len(to) > len(from) {
		return fmt.Errorf("cannot grow string: %d > %d", len(to), len(from))
	}

	offset, size := e.str64()

	pos := offset
	for pos < offset+size {
		if e.data[pos] == 0 {
			pos += 1
			continue
		}
		zero := bytes.IndexByte(e.data[pos:], 0x00)
		if zero == -1 {
			break
		}
		s := string(e.data[pos : pos+zero])
		if s == from {
			copy(e.data[pos:pos+len(to)], to)
			// Pan with zeroes if necessary, until the previous end mark:
			copy(e.data[pos+len(to):pos+zero], make([]byte, zero-len(to)))
			return nil
		}
		pos += zero
	}

	return fmt.Errorf("string not found: %q", from)
}

func (e *elf) RmDtNeeded64(dep string) error {
	offset := 0
	found := false
	stro, _ := e.str64()
	var prev *C.Elf64_Dyn
	for _, d := range e.PTDynamic64() {
		if d.d_tag == C.DT_NEEDED {
			offset = int(*(*C.Elf64_Addr)(unsafe.Pointer(&d.d_un[0])))
			if string(e.data[stro+offset:stro+offset+len(dep)+1]) == dep+"\x00" {
				found = true
				prev = d
				continue
			}
		}
		if !found {
			continue
		}
		// Move back the current entry:
		prev.d_tag = d.d_tag
		copy(prev.d_un[:], d.d_un[:])
		prev = d
	}
	if !found {
		return fmt.Errorf("dependency not found: %q", dep)
	}

	// Zero out the last entry:
	prev.d_tag = C.DT_NULL
	zeros := make([]byte, len(prev.d_un))
	copy(prev.d_un[:], zeros)

	return nil
}

func (e *elf) str64() (offset, size int) {
	found := false
	for _, d := range e.PTDynamic64() {
		if d.d_tag == C.DT_STRTAB {
			offset = int(*(*C.Elf64_Addr)(unsafe.Pointer(&d.d_un[0])))
		} else if d.d_tag == C.DT_STRSZ {
			size = int(*(*C.Elf64_Xword)(unsafe.Pointer(&d.d_un[0])))
		} else {
			continue
		}
		if found {
			return
		}
		found = true
	}
	return
}
