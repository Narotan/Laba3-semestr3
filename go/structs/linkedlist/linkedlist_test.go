package linkedlist

import (
	"encoding/json"
	"testing"
)

func TestLinkedListNew(t *testing.T) {
	l := New()
	if l.Size() != 0 {
		t.Errorf("Expected size 0, got %d", l.Size())
	}
}

func TestLinkedListPushFront(t *testing.T) {
	l := New()
	l.PushFront("third")
	l.PushFront("second")
	l.PushFront("first")

	val, _ := l.Get(0)
	if val != "first" {
		t.Errorf("Expected 'first', got '%s'", val)
	}
}

func TestLinkedListPushBack(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")
	l.PushBack("third")

	val, _ := l.Get(2)
	if val != "third" {
		t.Errorf("Expected 'third', got '%s'", val)
	}
}

func TestLinkedListRemoveByValue(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")
	l.PushBack("third")

	if !l.RemoveByValue("second") {
		t.Error("Expected RemoveByValue to return true")
	}

	if l.Size() != 2 {
		t.Errorf("Expected size 2, got %d", l.Size())
	}
}

func TestLinkedListSerialization(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")
	l.PushBack("third")

	data, err := json.Marshal(l)
	if err != nil {
		t.Fatalf("Marshal error: %v", err)
	}

	l2 := New()
	err = json.Unmarshal(data, l2)
	if err != nil {
		t.Fatalf("Unmarshal error: %v", err)
	}

	if l2.Size() != 3 {
		t.Errorf("Expected size 3, got %d", l2.Size())
	}
}

func BenchmarkLinkedListPushBack(b *testing.B) {
	l := New()
	for i := 0; i < b.N; i++ {
		l.PushBack("test")
	}
}
