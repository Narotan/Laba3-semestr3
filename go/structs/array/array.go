package array

import (
	"encoding/json"
	"fmt"
)

// Array represents a dynamic array
type Array struct {
	data     []string
	size     int
	capacity int
}

// New creates a new Array with default capacity
func New() *Array {
	return &Array{
		data:     make([]string, 10),
		size:     0,
		capacity: 10,
	}
}

// NewWithCapacity creates a new Array with specified capacity
func NewWithCapacity(capacity int) *Array {
	if capacity <= 0 {
		capacity = 10
	}
	return &Array{
		data:     make([]string, capacity),
		size:     0,
		capacity: capacity,
	}
}

// Size returns the number of elements
func (a *Array) Size() int {
	return a.size
}

// IsEmpty checks if array is empty
func (a *Array) IsEmpty() bool {
	return a.size == 0
}

// resize doubles the capacity
func (a *Array) resize() {
	a.capacity *= 2
	newData := make([]string, a.capacity)
	copy(newData, a.data)
	a.data = newData
}

// Append adds an element to the end
func (a *Array) Append(value string) {
	if a.size >= a.capacity {
		a.resize()
	}
	a.data[a.size] = value
	a.size++
}

// Insert adds an element at specified index
func (a *Array) Insert(index int, value string) error {
	if index < 0 || index > a.size {
		return fmt.Errorf("index out of range: %d", index)
	}
	if a.size >= a.capacity {
		a.resize()
	}

	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.size++
	return nil
}

// Get returns element at index
func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= a.size {
		return "", fmt.Errorf("index out of range: %d", index)
	}
	return a.data[index], nil
}

// Set updates element at index
func (a *Array) Set(index int, value string) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range: %d", index)
	}
	a.data[index] = value
	return nil
}

// Remove deletes element at index
func (a *Array) Remove(index int) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range: %d", index)
	}

	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.size--
	return nil
}

// RemoveByValue removes first occurrence of value
func (a *Array) RemoveByValue(value string) bool {
	for i := 0; i < a.size; i++ {
		if a.data[i] == value {
			a.Remove(i)
			return true
		}
	}
	return false
}

// Clear removes all elements
func (a *Array) Clear() {
	a.size = 0
}

// ToSlice returns a copy of internal data
func (a *Array) ToSlice() []string {
	result := make([]string, a.size)
	copy(result, a.data[:a.size])
	return result
}

// MarshalJSON implements json.Marshaler
func (a *Array) MarshalJSON() ([]byte, error) {
	return json.Marshal(a.data[:a.size])
}

// UnmarshalJSON implements json.Unmarshaler
func (a *Array) UnmarshalJSON(data []byte) error {
	var items []string
	if err := json.Unmarshal(data, &items); err != nil {
		return err
	}

	a.size = 0
	a.capacity = len(items) * 2
	if a.capacity < 10 {
		a.capacity = 10
	}
	a.data = make([]string, a.capacity)

	for _, item := range items {
		a.Append(item)
	}
	return nil
}
