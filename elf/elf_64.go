package elf

// #include <elf.h>
import "C"

import (
	"bytes"
	"fmt"
	"sort"
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

func (e *elf) StrMap64() map[int]string {
	offset, size := e.str64()

	pos := offset
	res := map[int]string{}
	for pos < offset+size {
		if e.data[pos] == 0 {
			pos += 1
			continue
		}
		zpos := bytes.IndexByte(e.data[pos:], 0x00)
		if zpos == -1 {
			break
		}
		res[pos-offset] = string(e.data[pos : pos+zpos])
		pos += zpos
	}

	return res
}

func (e *elf) StrTab64() []string {
	m := e.StrMap64()
	keys := make([]int, len(m))

	i := 0
	for key := range m {
		keys[i] = key
		i++
	}
	sort.Ints(keys)

	vals := make([]string, len(m))
	for i, key := range keys {
		vals[i] = m[key]
	}
	return vals
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
	found := false
	sm := e.StrMap64()
	var prev *C.Elf64_Dyn
	dynmap := map[C.Elf64_Sxword][](*C.Elf64_Dyn){}
	for _, d := range e.PTDynamic64() {
		if d.d_tag == C.DT_NEEDED {
			if sm[int(*(*C.Elf64_Addr)(unsafe.Pointer(&d.d_un[0])))] == dep {
				found = true
				prev = d
				continue
			}
		}
		if !found {
			dynmap[d.d_tag] = append(dynmap[d.d_tag], d)
			continue
		}
		// Move back the current entry:
		prev.d_tag = d.d_tag
		copy(prev.d_un[:], d.d_un[:])
		dynmap[d.d_tag] = append(dynmap[d.d_tag], prev)
		prev = d
	}
	if !found {
		return fmt.Errorf("dependency not found: %q", dep)
	}

	// Zero out the last entry:
	prev.d_tag = C.DT_NULL
	zeros := make([]byte, len(prev.d_un))
	copy(prev.d_un[:], zeros)

	if len(dynmap[C.DT_VERNEED]) == 0 {
		// DT_VERNEED section not found.
		return nil
	}
	if n := len(dynmap[C.DT_VERNEED]); n != 1 {
		return fmt.Errorf("expected at most one dt_verneed section, found: %d", n)
	}
	if n := len(dynmap[C.DT_VERNEEDNUM]); n != 1 {
		return fmt.Errorf("expected exactly one dt_verneednum, found: %d", n)
	}

	var vprev *C.Elf64_Verneed
	dtoffs := dynmap[C.DT_VERNEED][0]
	dtsize := dynmap[C.DT_VERNEEDNUM][0]

	voffset := int(*(*C.Elf64_Addr)(unsafe.Pointer(&dtoffs.d_un[0])))
	vsize := int(*(*C.Elf64_Xword)(unsafe.Pointer(&dtsize.d_un[0])))
	newOffset := voffset
	newSize := vsize

	for n := 0; n < vsize; n++ {
		vn := (*C.Elf64_Verneed)(unsafe.Pointer(&e.data[voffset]))
		if vn.vn_version != C.VER_NEED_CURRENT {
			return fmt.Errorf("bad vn_version, expected %d, got: %d", C.VER_NEED_CURRENT, vn.vn_version)
		}

		if sm[int(vn.vn_file)] != dep {
			voffset += int(vn.vn_next)
			vprev = vn
			continue
		}

		if n == 0 {
			// This is the first Elf64_Verneed entry; point here directly.
			newOffset = voffset
		} else if vn.vn_next > 0 {
			// This is not the first, nor the last Elf64_Verneed entry; re-link prev to next.
			vprev.vn_next += vn.vn_next
		} else {
			// This is the last  Elf64_Verneed entry; mark the previous one as last.
			vprev.vn_next = 0
		}

		vnaoffset := voffset + int(vn.vn_aux)
		for {
			vna := (*C.Elf64_Vernaux)(unsafe.Pointer(&e.data[vnaoffset]))
			fmt.Printf("TODO: RM version deps: %q\n", sm[int(vna.vna_name)])
			vnaoffset += int(vna.vna_next)

			if vna.vna_next == 0 {
				break
			}
		}

		newSize -= 1
		voffset += int(vn.vn_next)
		vprev = vn
	}
	if newOffset == voffset && newSize == vsize {
		// Nothing to update.
		return nil
	}

	if newSize == 0 {
		e.RmDt64(C.DT_VERNEED)
		e.RmDt64(C.DT_VERNEEDNUM)
		return nil
	}

	// Update DT_VERNEED & DT_VERNEEDNUM entries.
	*(*C.Elf64_Addr)(unsafe.Pointer(&dtoffs.d_un[0])) = C.Elf64_Addr(newOffset)
	*(*C.Elf64_Xword)(unsafe.Pointer(&dtsize.d_un[0])) = C.Elf64_Xword(newSize)
	return nil

}

func (e *elf) RmDt64(tag C.Elf64_Sxword) {
	found := false
	var prev *C.Elf64_Dyn
	for _, d := range e.PTDynamic64() {
		if d.d_tag == tag {
			found = true
			prev = d
			continue
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
		return
	}

	// Zero out the last entry:
	prev.d_tag = C.DT_NULL
	zeros := make([]byte, len(prev.d_un))
	copy(prev.d_un[:], zeros)
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
