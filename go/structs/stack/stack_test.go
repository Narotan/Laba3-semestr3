package stack

import (
	"encoding/json"
	"testing"
)

func TestStackNew(t *testing.T) {
	s := New()
	if s.Size() != 0 {
		t.Errorf("Expected size 0, got %d", s.Size())
	}
	if !s.IsEmpty() {
		t.Error("Expected stack to be empty")
	}
}

func TestStackPush(t *testing.T) {
	s := New()
	s.Push("first")
	s.Push("second")
	s.Push("third")

	if s.Size() != 3 {
		t.Errorf("Expected size 3, got %d", s.Size())
	}
}

func TestStackPop(t *testing.T) {
	s := New()
	s.Push("first")
	s.Push("second")
	s.Push("third")

	val, _ := s.Pop()
	if val != "third" {
		t.Errorf("Expected 'third', got '%s'", val)
	}

	if s.Size() != 2 {
		t.Errorf("Expected size 2, got %d", s.Size())
	}
}

func TestStackPeek(t *testing.T) {
	s := New()
	s.Push("first")
	s.Push("second")

	val, _ := s.Peek()
	if val != "second" {
		t.Errorf("Expected 'second', got '%s'", val)
	}

	if s.Size() != 2 {
		t.Error("Peek should not remove element")
	}
}

func TestStackLIFO(t *testing.T) {
	s := New()
	s.Push("1")
	s.Push("2")
	s.Push("3")

	expected := []string{"3", "2", "1"}
	for _, exp := range expected {
		val, _ := s.Pop()
		if val != exp {
			t.Errorf("Expected '%s', got '%s'", exp, val)
		}
	}
}

func TestStackPopEmpty(t *testing.T) {
	s := New()
	_, err := s.Pop()
	if err == nil {
		t.Error("Expected error when popping from empty stack")
	}
}

func TestStackSerialization(t *testing.T) {
	s := New()
	s.Push("bottom")
	s.Push("middle")
	s.Push("top")

	data, err := json.Marshal(s)
	if err != nil {
		t.Fatalf("Marshal error: %v", err)
	}

	s2 := New()
	err = json.Unmarshal(data, s2)
	if err != nil {
		t.Fatalf("Unmarshal error: %v", err)
	}

	val1, _ := s2.Pop()
	val2, _ := s2.Pop()
	val3, _ := s2.Pop()

	if val1 != "top" || val2 != "middle" || val3 != "bottom" {
		t.Error("Stack order not preserved after serialization")
	}
}

func BenchmarkStackPush(b *testing.B) {
	s := New()
	for i := 0; i < b.N; i++ {
		s.Push("test")
	}
}

func BenchmarkStackPop(b *testing.B) {
	s := New()
	for i := 0; i < b.N; i++ {
		s.Push("test")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		s.Pop()
	}
}
