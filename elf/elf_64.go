package elf

// #include <linux/elf.h>
import "C"

import (
	"bytes"
	"fmt"
	"unsafe"
)

var Class64 class = C.ELFCLASS64

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
		zpos := bytes.IndexByte(e.data[pos:], 0x00)
		if zpos == -1 {
			break
		}
		res = append(res, string(e.data[pos:pos+zpos]))
		pos += zpos
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
		zpos := bytes.IndexByte(e.data[pos:], 0x00)
		if zpos == -1 {
			break
		}
		s := string(e.data[pos : pos+zpos])
		if s == from {
			copy(e.data[pos:pos+len(to)], to)
			// Pad with zeroes if necessary, until the previous end mark:
			copy(e.data[pos+len(to):pos+zpos], make([]byte, zpos-len(to)))
			return nil
		}
		pos += zpos
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
