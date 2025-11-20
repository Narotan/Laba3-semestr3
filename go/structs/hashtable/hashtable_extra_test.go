package hashtable

import (
	"encoding/json"
	"strconv"
	"testing"
)

func TestHashTableRemoveAndRehash(t *testing.T) {
	ht := New()
	// insert many keys to trigger rehash
	for i := 0; i < 100; i++ {
		k := "k" + strconv.Itoa(i)
		ht.Insert(k, "v")
	}

	// remove a key that doesn't exist
	ht.Remove("nonexistent")

	// insert and remove specific keys
	ht.Insert("alpha", "1")
	if !ht.Contains("alpha") {
		t.Error("Expected alpha to be present")
	}
	ht.Remove("alpha")
	if ht.Contains("alpha") {
		t.Error("Expected alpha to be removed")
	}

	// ToMap and Clear
	ht.Insert("a", "A")
	m := ht.ToMap()
	if m["a"] != "A" {
		t.Error("ToMap missing entry a")
	}
	ht.Clear()
	if !ht.IsEmpty() {
		t.Error("Expected empty after Clear")
	}
}

func TestHashTableGetErrorsAndUnmarshalInvalid(t *testing.T) {
	ht := New()
	_, err := ht.Get("missing")
	if err == nil {
		t.Error("Expected error for missing key")
	}

	// invalid JSON for Unmarshal
	ht2 := New()
	bad := []byte("{invalid json}")
	if err := json.Unmarshal(bad, ht2); err == nil {
		t.Error("Expected error for invalid JSON Unmarshal")
	}
}
