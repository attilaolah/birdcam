package nikon

import (
	"errors"
	"testing"
)

func TestInit(t *testing.T) {
	ls := New(42)
	defer ls.Free()
}

func TestStage1(t *testing.T) {
	ls := New(1)
	defer ls.Free()

	if got, err := ls.Stage1(); err != nil {
		t.Errorf("Stage1(): %v", err)
	} else if want := uint64(7749363893351949254); got != want {
		t.Errorf("Stage1(): want: %d, got: %d", want, got)
	}

	// Calling Stage1() again: wrong stage.
	if _, err := ls.Stage1(); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage1(): want: %v, got: %v", ErrWrongStage, err)
	}
}

func TestStage2(t *testing.T) {
	ls_a := New(2)
	defer ls_a.Free()

	stage_1, err := ls_a.Stage1()
	if err != nil {
		t.Errorf("Stage1(): %v", err)
	}
	if want := uint64(6465365841803442559); stage_1 != want {
		t.Errorf("Stage1(): want: %d, got: %d", want, stage_1)
	}

	ls_b := New(1)
	defer ls_b.Free()

	if nonce, device_id, err := ls_b.Stage2(stage_1); err != nil {
		t.Errorf("Stage2(): %v", err)
	} else if want := uint64(7749363893351949254); nonce != want {
		t.Errorf("Stage2()[0]: want %d, got %d", want, nonce)
	} else if want := uint64(3692570941250695308); device_id != want {
		t.Errorf("Stage2()[1]: want %d, got: %d", want, device_id)
	}

	// Calling Stage2() again: wrong stage.
	if _, _, err := ls_a.Stage2(stage_1); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage2(): want: %v, got: %v", ErrWrongStage, err)
	}
}

func TestStage3(t *testing.T) {
	ls_a := New(3)
	defer ls_a.Free()

	// Calling Stage3() before Stage1(): wrong stage.
	if _, err := ls_a.Stage3(0, 0, 0); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage3(): want: %v, got: %v", ErrWrongStage, err)
	}

	stage_1, err := ls_a.Stage1()
	if err != nil {
		t.Errorf("Stage1(): %v", err)
	}

	// Calling Stage3() with wrong data: auth error.
	if _, err := ls_a.Stage3(0, 0, 0); !errors.Is(err, ErrAuth) {
		t.Errorf("Stage3(): want: %v, got: %v", ErrAuth, err)
	}
	if _, err := ls_a.Stage3(1, stage_1, 3); !errors.Is(err, ErrAuth) {
		t.Errorf("Stage3(): want: %v, got: %v", ErrAuth, err)
	}

	ls_b := New(1)
	defer ls_b.Free()

	nonce, device_id, err := ls_b.Stage2(stage_1)
	if err != nil {
		t.Errorf("Stage2(): %v", err)
	}

	if stage_3, err := ls_a.Stage3(nonce, stage_1, device_id); err != nil {
		t.Errorf("Stage3(): %v", err)
	} else if want := uint64(1123151823067396199); stage_3 != want {
		t.Errorf("Stage3(): want %v, got: %v", want, stage_3)
	}

	// Calling Stage3() again: wrong stage.
	if _, err := ls_a.Stage3(nonce, stage_1, device_id); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage3(): want: %v, got: %v", ErrWrongStage, err)
	}
}

func TestStage4(t *testing.T) {
	ls_a := New(4)
	defer ls_a.Free()
	ls_b := New(4)
	defer ls_b.Free()

	// Calling Stage4() before stage_2(): wrong stage.
	if err := ls_b.Stage4(0, 0, 0); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage4(): want: %v, got: %v", ErrWrongStage, err)
	}

	stage_1, err := ls_a.Stage1()
	if err != nil {
		t.Errorf("Stage1(): %v", err)
	}
	nonce, device_id, err := ls_b.Stage2(stage_1)
	if err != nil {
		t.Errorf("Stage2(): %v", err)
	}
	stage_3, err := ls_a.Stage3(nonce, stage_1, device_id)
	if err != nil {
		t.Errorf("Stage3(): %v", err)
	}

	// Calling Stage4() with wrong data: auth error.
	if err := ls_b.Stage4(0, 0, 0); !errors.Is(err, ErrAuth) {
		t.Errorf("Stage3(): want: %v, got: %v", ErrAuth, err)
	}

	// No exception.
	if err := ls_b.Stage4(nonce, stage_1, stage_3); err != nil {
		t.Errorf("Stage4(): %v", err)
	}

	// Calling Stage3() again: wrong stage.
	if err := ls_b.Stage4(nonce, stage_1, stage_3); !errors.Is(err, ErrWrongStage) {
		t.Errorf("Stage4(): want: %v, got: %v", ErrWrongStage, err)
	}
}
