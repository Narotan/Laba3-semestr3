package bst

import (
	"encoding/json"
	"testing"
)

func TestBSTNew(t *testing.T) {
	bst := New()
	if bst.Size() != 0 {
		t.Errorf("Expected size 0, got %d", bst.Size())
	}
}

func TestBSTInsert(t *testing.T) {
	bst := New()
	bst.Insert("dog")
	bst.Insert("cat")
	bst.Insert("elephant")

	if bst.Size() != 3 {
		t.Errorf("Expected size 3, got %d", bst.Size())
	}
}

func TestBSTSearch(t *testing.T) {
	bst := New()
	bst.Insert("apple")
	bst.Insert("banana")

	if !bst.Search("apple") {
		t.Error("Expected to find 'apple'")
	}

	if bst.Search("orange") {
		t.Error("Expected not to find 'orange'")
	}
}

func TestBSTRemove(t *testing.T) {
	bst := New()
	bst.Insert("dog")
	bst.Insert("cat")
	bst.Insert("elephant")

	bst.Remove("cat")
	if bst.Search("cat") {
		t.Error("Expected 'cat' to be removed")
	}

	if bst.Size() != 2 {
		t.Errorf("Expected size 2, got %d", bst.Size())
	}
}

func TestBSTSerialization(t *testing.T) {
	bst := New()
	bst.Insert("dog")
	bst.Insert("cat")
	bst.Insert("elephant")

	data, _ := json.Marshal(bst)
	bst2 := New()
	json.Unmarshal(data, bst2)

	if bst2.Size() != 3 {
		t.Errorf("Expected size 3, got %d", bst2.Size())
	}

	if !bst2.Search("dog") {
		t.Error("Expected to find 'dog' after deserialization")
	}
}

func BenchmarkBSTInsert(b *testing.B) {
	bst := New()
	for i := 0; i < b.N; i++ {
		bst.Insert("test")
	}
}

func BenchmarkBSTSearch(b *testing.B) {
	bst := New()
	for i := 0; i < 1000; i++ {
		bst.Insert("item")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		bst.Search("item")
	}
}
