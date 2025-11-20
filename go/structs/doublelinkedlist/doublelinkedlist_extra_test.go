package doublelinkedlist

import (
	"encoding/json"
	"testing"
)

func TestDoubleLinkedListFrontAndBackAndErrors(t *testing.T) {
	l := New()
	// empty pops
	if err := l.PopFront(); err == nil {
		t.Error("Expected PopFront error on empty")
	}
	if err := l.PopBack(); err == nil {
		t.Error("Expected PopBack error on empty")
	}

	// push front/back and get via tail-optimized path
	l.PushBack("one")
	l.PushBack("two")
	l.PushBack("three")
	l.PushFront("zero")

	if v, _ := l.Get(3); v != "three" {
		t.Errorf("Expected 'three', got %s", v)
	}

	// ToSlice and Clear
	sl := l.ToSlice()
	if len(sl) != l.Size() {
		t.Error("ToSlice size mismatch")
	}
	l.Clear()
	if !l.IsEmpty() {
		t.Error("Expected empty after Clear")
	}
}

func TestDoubleLinkedListUnmarshalInvalid(t *testing.T) {
	l := New()
	bad := []byte("notjson")
	if err := json.Unmarshal(bad, l); err == nil {
		t.Error("Expected error for invalid JSON Unmarshal")
	}
}

func TestDoubleLinkedListSerializationAndPops(t *testing.T) {
	l := New()
	l.PushBack("a")
	l.PushBack("b")
	l.PushBack("c")

	data, err := json.Marshal(l)
	if err != nil {
		t.Fatalf("Marshal failed: %v", err)
	}
	l2 := New()
	if err := json.Unmarshal(data, l2); err != nil {
		t.Fatalf("Unmarshal failed: %v", err)
	}
	if l2.Size() != 3 {
		t.Errorf("Expected size 3 after unmarshal, got %d", l2.Size())
	}

	// pop front/back until empty
	for !l2.IsEmpty() {
		_ = l2.PopFront()
	}
	if !l2.IsEmpty() {
		t.Error("Expected empty after popping all elements")
	}
	if err := l2.PopBack(); err == nil {
		t.Error("Expected error popping back from empty")
	}
}
