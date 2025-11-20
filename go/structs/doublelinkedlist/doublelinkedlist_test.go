package doublelinkedlist

import (
	"encoding/json"
	"testing"
)

func TestDoubleLinkedListNew(t *testing.T) {
	l := New()
	if l.Size() != 0 {
		t.Errorf("Expected size 0, got %d", l.Size())
	}
}

func TestDoubleLinkedListPushBack(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")

	val, _ := l.Get(1)
	if val != "second" {
		t.Errorf("Expected 'second', got '%s'", val)
	}
}

func TestDoubleLinkedListPopFront(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")

	l.PopFront()
	if l.Size() != 1 {
		t.Errorf("Expected size 1, got %d", l.Size())
	}
}

func TestDoubleLinkedListPopBack(t *testing.T) {
	l := New()
	l.PushBack("first")
	l.PushBack("second")

	l.PopBack()
	if l.Size() != 1 {
		t.Errorf("Expected size 1, got %d", l.Size())
	}
}

func TestDoubleLinkedListSerialization(t *testing.T) {
	l := New()
	l.PushBack("a")
	l.PushBack("b")
	l.PushBack("c")

	data, _ := json.Marshal(l)
	l2 := New()
	json.Unmarshal(data, l2)

	if l2.Size() != 3 {
		t.Errorf("Expected size 3, got %d", l2.Size())
	}
}

func BenchmarkDoubleLinkedListPushBack(b *testing.B) {
	l := New()
	for i := 0; i < b.N; i++ {
		l.PushBack("test")
	}
}
