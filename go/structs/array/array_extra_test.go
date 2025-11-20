package array

import (
	"encoding/json"
	"testing"
)

func TestArrayNewWithCapacityAndUnmarshalInvalid(t *testing.T) {
	a := NewWithCapacity(-5)
	if a == nil {
		t.Fatal("Expected non-nil array")
	}

	bad := []byte("badjson")
	if err := json.Unmarshal(bad, a); err == nil {
		t.Error("Expected error for invalid JSON Unmarshal")
	}
}
