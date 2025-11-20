package bst

import (
	"encoding/json"
	"testing"
)

func TestBSTRemoveCasesAndInOrder(t *testing.T) {
	bst := New()
	// build tree: d b f a c e g
	for _, v := range []string{"d", "b", "f", "a", "c", "e", "g"} {
		bst.Insert(v)
	}

	// InOrder should be sorted
	got := bst.InOrder()
	want := []string{"a", "b", "c", "d", "e", "f", "g"}
	if len(got) != len(want) {
		t.Fatalf("InOrder length mismatch: got %v", got)
	}
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("InOrder mismatch at %d: got %s want %s", i, got[i], want[i])
		}
	}

	// remove leaf
	bst.Remove("a")
	if bst.Search("a") {
		t.Error("Expected 'a' removed")
	}

	// remove node with one child
	bst.Remove("f") // f has child g
	if bst.Search("f") {
		t.Error("Expected 'f' removed")
	}

	// remove node with two children
	bst.Remove("b")
	if bst.Search("b") {
		t.Error("Expected 'b' removed")
	}
}

func TestBSTUnmarshalInvalid(t *testing.T) {
	bst := New()
	bad := []byte("{invalid}")
	if err := json.Unmarshal(bad, bst); err == nil {
		t.Error("Expected error for invalid JSON Unmarshal")
	}
}
