package linkedlist

import (
	"encoding/json"
	"testing"
)

func TestLinkedListErrorsAndClear(t *testing.T) {
	l := New()
	// Get on empty
	if _, err := l.Get(0); err == nil {
		t.Error("Expected error for Get on empty")
	}
	if err := l.PopFront(); err == nil {
		t.Error("Expected error for PopFront on empty")
	}

	// Insert out of range
	if err := l.Insert(5, "x"); err == nil {
		t.Error("Expected error for Insert out of range")
	}

	// Push and test Set, Remove
	l.PushBack("a")
	l.PushBack("b")
	l.PushBack("c")

	if err := l.Set(1, "B"); err != nil {
		t.Fatalf("Set failed: %v", err)
	}
	if v, _ := l.Get(1); v != "B" {
		t.Errorf("Expected 'B', got '%s'", v)
	}

	if err := l.Remove(1); err != nil {
		t.Fatalf("Remove failed: %v", err)
	}

	// RemoveByValue false
	if l.RemoveByValue("notfound") {
		t.Error("Expected RemoveByValue to return false")
	}

	// ToSlice and Clear
	sl := l.ToSlice()
	if len(sl) != l.Size() {
		t.Error("ToSlice length mismatch")
	}
	l.Clear()
	if !l.IsEmpty() {
		t.Error("Expected empty after Clear")
	}
}

func TestLinkedListUnmarshalInvalid(t *testing.T) {
	l := New()
	bad := []byte("not json")
	if err := json.Unmarshal(bad, l); err == nil {
		t.Error("Expected error for invalid JSON Unmarshal")
	}
}

func TestLinkedListInsertPopAndSerialization(t *testing.T) {
	l := New()
	l.PushBack("one")
	l.PushBack("three")
	if err := l.Insert(1, "two"); err != nil {
		t.Fatalf("Insert failed: %v", err)
	}

	// check order
	sl := l.ToSlice()
	if len(sl) != 3 || sl[0] != "one" || sl[1] != "two" || sl[2] != "three" {
		t.Fatalf("Unexpected slice: %v", sl)
	}

	// pop front until empty
	for !l.IsEmpty() {
		if err := l.PopFront(); err != nil {
			t.Fatalf("PopFront failed: %v", err)
		}
	}

	// serialize empty list
	data, err := json.Marshal(l)
	if err != nil {
		t.Fatalf("Marshal failed: %v", err)
	}
	l2 := New()
	if err := json.Unmarshal(data, l2); err != nil {
		t.Fatalf("Unmarshal failed: %v", err)
	}
	if !l2.IsEmpty() {
		t.Error("Expected empty after unmarshal of empty list")
	}
}
