package hashtable

import (
	"encoding/json"
	"testing"
)

func TestHashTableNew(t *testing.T) {
	ht := New()
	if ht.Size() != 0 {
		t.Errorf("Expected size 0, got %d", ht.Size())
	}
}

func TestHashTableInsert(t *testing.T) {
	ht := New()
	ht.Insert("key1", "value1")
	ht.Insert("key2", "value2")

	if ht.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ht.Size())
	}
}

func TestHashTableGet(t *testing.T) {
	ht := New()
	ht.Insert("name", "John")

	val, err := ht.Get("name")
	if err != nil || val != "John" {
		t.Errorf("Expected 'John', got '%s'", val)
	}
}

func TestHashTableContains(t *testing.T) {
	ht := New()
	ht.Insert("key1", "value1")

	if !ht.Contains("key1") {
		t.Error("Expected key1 to be present")
	}

	if ht.Contains("key2") {
		t.Error("Expected key2 to be absent")
	}
}

func TestHashTableSerialization(t *testing.T) {
	ht := New()
	ht.Insert("key1", "value1")
	ht.Insert("key2", "value2")

	data, _ := json.Marshal(ht)
	ht2 := New()
	json.Unmarshal(data, ht2)

	if ht2.Size() != 2 {
		t.Errorf("Expected size 2, got %d", ht2.Size())
	}
}

func BenchmarkHashTableInsert(b *testing.B) {
	ht := New()
	for i := 0; i < b.N; i++ {
		ht.Insert("key", "value")
	}
}
