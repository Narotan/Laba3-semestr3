package stack

import (
	"encoding/json"
	"fmt"
)

// Node represents a stack node
type Node struct {
	Data string
	Next *Node
}

// Stack represents a LIFO data structure
type Stack struct {
	top  *Node
	size int
}

// New creates a new Stack
func New() *Stack {
	return &Stack{
		top:  nil,
		size: 0,
	}
}

// Push adds an element to the top
func (s *Stack) Push(value string) {
	newNode := &Node{
		Data: value,
		Next: s.top,
	}
	s.top = newNode
	s.size++
}

// Pop removes and returns the top element
func (s *Stack) Pop() (string, error) {
	if s.top == nil {
		return "", fmt.Errorf("stack is empty")
	}

	value := s.top.Data
	s.top = s.top.Next
	s.size--
	return value, nil
}

// Peek returns the top element without removing it
func (s *Stack) Peek() (string, error) {
	if s.top == nil {
		return "", fmt.Errorf("stack is empty")
	}
	return s.top.Data, nil
}

// Size returns the number of elements
func (s *Stack) Size() int {
	return s.size
}

// IsEmpty checks if stack is empty
func (s *Stack) IsEmpty() bool {
	return s.size == 0
}

// Clear removes all elements
func (s *Stack) Clear() {
	s.top = nil
	s.size = 0
}

// ToSlice returns all elements as slice (top to bottom)
func (s *Stack) ToSlice() []string {
	result := make([]string, 0, s.size)
	current := s.top
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// MarshalJSON implements json.Marshaler
func (s *Stack) MarshalJSON() ([]byte, error) {
	return json.Marshal(s.ToSlice())
}

// UnmarshalJSON implements json.Unmarshaler
func (s *Stack) UnmarshalJSON(data []byte) error {
	var items []string
	if err := json.Unmarshal(data, &items); err != nil {
		return err
	}

	s.Clear()
	// Push in reverse order to maintain stack order
	for i := len(items) - 1; i >= 0; i-- {
		s.Push(items[i])
	}
	return nil
}
