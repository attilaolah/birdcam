package nikon_test

import (
	"errors"
	"testing"

	ls_sec "github.com/attilaolah/birdcam/nikon"
)

func TestInit(t *testing.T) {
	ls := ls_sec.New(42)
	defer ls.Free()
}

func TestStage1(t *testing.T) {
	ls := ls_sec.New(1)
	defer ls.Free()

	if got, err := ls.Stage1(); err != nil {
		t.Errorf("Stage1(): %v", err)
	} else if want := uint64(7749363893351949254); got != want {
		t.Errorf("Stage1(): want: %d, got: %d", want, got)
	}

	if _, err := ls.Stage1(); !errors.Is(err, ls_sec.ErrWrongStage) {
		t.Errorf("Stage1(): want: ErrWrongStage, got: %v", err)
	}
}
