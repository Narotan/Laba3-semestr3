package array

import (
	"encoding/json"
	"testing"
)

func TestArrayNew(t *testing.T) {
	arr := New()
	if arr.Size() != 0 {
		t.Errorf("Expected size 0, got %d", arr.Size())
	}
	if !arr.IsEmpty() {
		t.Error("Expected array to be empty")
	}
}

func TestArrayAppend(t *testing.T) {
	arr := New()
	arr.Append("first")
	arr.Append("second")
	arr.Append("third")

	if arr.Size() != 3 {
		t.Errorf("Expected size 3, got %d", arr.Size())
	}

	val, _ := arr.Get(0)
	if val != "first" {
		t.Errorf("Expected 'first', got '%s'", val)
	}
}

func TestArrayInsert(t *testing.T) {
	arr := New()
	arr.Append("first")
	arr.Append("third")
	arr.Insert(1, "second")

	val, _ := arr.Get(1)
	if val != "second" {
		t.Errorf("Expected 'second', got '%s'", val)
	}
}

func TestArraySet(t *testing.T) {
	arr := New()
	arr.Append("original")
	arr.Set(0, "modified")

	val, _ := arr.Get(0)
	if val != "modified" {
		t.Errorf("Expected 'modified', got '%s'", val)
	}
}

func TestArrayRemove(t *testing.T) {
	arr := New()
	arr.Append("first")
	arr.Append("second")
	arr.Append("third")

	arr.Remove(1)
	if arr.Size() != 2 {
		t.Errorf("Expected size 2, got %d", arr.Size())
	}

	val, _ := arr.Get(1)
	if val != "third" {
		t.Errorf("Expected 'third', got '%s'", val)
	}
}

func TestArrayRemoveByValue(t *testing.T) {
	arr := New()
	arr.Append("first")
	arr.Append("second")
	arr.Append("third")

	if !arr.RemoveByValue("second") {
		t.Error("Expected RemoveByValue to return true")
	}

	if arr.Size() != 2 {
		t.Errorf("Expected size 2, got %d", arr.Size())
	}

	if arr.RemoveByValue("nonexistent") {
		t.Error("Expected RemoveByValue to return false for nonexistent value")
	}
}

func TestArrayClear(t *testing.T) {
	arr := New()
	arr.Append("first")
	arr.Append("second")
	arr.Clear()

	if arr.Size() != 0 {
		t.Errorf("Expected size 0, got %d", arr.Size())
	}
}

func TestArrayOutOfRange(t *testing.T) {
	arr := New()
	arr.Append("first")

	_, err := arr.Get(10)
	if err == nil {
		t.Error("Expected error for out of range access")
	}

	err = arr.Set(10, "value")
	if err == nil {
		t.Error("Expected error for out of range set")
	}
}

func TestArraySerialization(t *testing.T) {
	arr := New()
	arr.Append("test1")
	arr.Append("test2")
	arr.Append("test3")

	data, err := json.Marshal(arr)
	if err != nil {
		t.Fatalf("Marshal error: %v", err)
	}

	arr2 := New()
	err = json.Unmarshal(data, arr2)
	if err != nil {
		t.Fatalf("Unmarshal error: %v", err)
	}

	if arr2.Size() != 3 {
		t.Errorf("Expected size 3, got %d", arr2.Size())
	}

	val, _ := arr2.Get(0)
	if val != "test1" {
		t.Errorf("Expected 'test1', got '%s'", val)
	}
}

func TestArrayResize(t *testing.T) {
	arr := New()
	// Add more than initial capacity
	for i := 0; i < 100; i++ {
		arr.Append("item")
	}

	if arr.Size() != 100 {
		t.Errorf("Expected size 100, got %d", arr.Size())
	}
}

// Benchmark tests
func BenchmarkArrayAppend(b *testing.B) {
	arr := New()
	for i := 0; i < b.N; i++ {
		arr.Append("test")
	}
}

func BenchmarkArrayGet(b *testing.B) {
	arr := New()
	for i := 0; i < 1000; i++ {
		arr.Append("test")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.Get(i % 1000)
	}
}

func BenchmarkArrayInsert(b *testing.B) {
	arr := New()
	for i := 0; i < 100; i++ {
		arr.Append("test")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.Insert(50, "inserted")
		arr.Remove(50)
	}
}
