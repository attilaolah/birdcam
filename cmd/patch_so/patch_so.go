package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"strings"

	"github.com/attilaolah/birdcam/elf"
)

var (
	src = flag.String("src", "", "Input file path. Must be a shared object (.so file).")
	dst = flag.String("dst", "", "Output file path.")

	patch strmap = map[string]string{}
)

type strmap map[string]string

func init() {
	flag.Var(&patch, "patch", "String table item (key=value) to patch. Can be repeated.")
}

func main() {
	flag.Parse()

	data, err := ioutil.ReadFile(*src)
	if err != nil {
		fmt.Printf("error reading source file %q: %v\n", *src, err)
		os.Exit(1)
	}

	so, err := elf.Parse(data)
	if err != nil {
		fmt.Println("error parsing source file:", err)
		os.Exit(1)
	}

	for k, v := range patch {
		if err := so.PatchStr64(k, v); err != nil {
			fmt.Println("error patching:", err)
			os.Exit(1)
		}
	}

	if *dst == "" {
		// No output path provided; quit silently.
		return
	}

	f, err := os.Create(*dst)
	if err != nil {
		fmt.Println("error creating output file %q: %v\n", *dst, err)
		os.Exit(1)
	}
	defer func() {
		if err := f.Close(); err != nil {
			fmt.Println("error closing file:", err)
			os.Exit(1)
		}
	}()

	if _, err := f.Write(so.Data()); err != nil {
		fmt.Println("error writing file:", err)
		os.Exit(1)
	}
}

func (m *strmap) String() string {
	return fmt.Sprint(*m)
}

func (m *strmap) Set(val string) error {
	// TODO: Use strings.Cut() when available!
	parts := strings.SplitN(val, "=", 2)
	if len(parts) != 2 {
		return fmt.Errorf("could not parse as key=val: %q", val)
	}

	(*m)[parts[0]] = parts[1]
	return nil
}
