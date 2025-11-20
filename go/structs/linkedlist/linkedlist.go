package linkedlist

import (
	"encoding/json"
	"fmt"
)

// Node represents a linked list node
type Node struct {
	Data string
	Next *Node
}

// LinkedList represents a singly linked list
type LinkedList struct {
	head *Node
	size int
}

// New creates a new LinkedList
func New() *LinkedList {
	return &LinkedList{
		head: nil,
		size: 0,
	}
}

// PushFront adds an element to the front
func (l *LinkedList) PushFront(value string) {
	newNode := &Node{
		Data: value,
		Next: l.head,
	}
	l.head = newNode
	l.size++
}

// PushBack adds an element to the back
func (l *LinkedList) PushBack(value string) {
	newNode := &Node{
		Data: value,
		Next: nil,
	}

	if l.head == nil {
		l.head = newNode
	} else {
		current := l.head
		for current.Next != nil {
			current = current.Next
		}
		current.Next = newNode
	}
	l.size++
}

// Insert adds an element at specified index
func (l *LinkedList) Insert(index int, value string) error {
	if index < 0 || index > l.size {
		return fmt.Errorf("index out of range: %d", index)
	}

	if index == 0 {
		l.PushFront(value)
		return nil
	}

	newNode := &Node{Data: value}
	current := l.head
	for i := 0; i < index-1; i++ {
		current = current.Next
	}
	newNode.Next = current.Next
	current.Next = newNode
	l.size++
	return nil
}

// Get returns element at index
func (l *LinkedList) Get(index int) (string, error) {
	if index < 0 || index >= l.size {
		return "", fmt.Errorf("index out of range: %d", index)
	}

	current := l.head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	return current.Data, nil
}

// Set updates element at index
func (l *LinkedList) Set(index int, value string) error {
	if index < 0 || index >= l.size {
		return fmt.Errorf("index out of range: %d", index)
	}

	current := l.head
	for i := 0; i < index; i++ {
		current = current.Next
	}
	current.Data = value
	return nil
}

// PopFront removes the first element
func (l *LinkedList) PopFront() error {
	if l.head == nil {
		return fmt.Errorf("list is empty")
	}

	l.head = l.head.Next
	l.size--
	return nil
}

// Remove deletes element at index
func (l *LinkedList) Remove(index int) error {
	if index < 0 || index >= l.size {
		return fmt.Errorf("index out of range: %d", index)
	}

	if index == 0 {
		return l.PopFront()
	}

	current := l.head
	for i := 0; i < index-1; i++ {
		current = current.Next
	}
	current.Next = current.Next.Next
	l.size--
	return nil
}

// RemoveByValue removes first occurrence of value
func (l *LinkedList) RemoveByValue(value string) bool {
	if l.head == nil {
		return false
	}

	if l.head.Data == value {
		l.PopFront()
		return true
	}

	current := l.head
	for current.Next != nil {
		if current.Next.Data == value {
			current.Next = current.Next.Next
			l.size--
			return true
		}
		current = current.Next
	}
	return false
}

// Size returns the number of elements
func (l *LinkedList) Size() int {
	return l.size
}

// IsEmpty checks if list is empty
func (l *LinkedList) IsEmpty() bool {
	return l.size == 0
}

// Clear removes all elements
func (l *LinkedList) Clear() {
	l.head = nil
	l.size = 0
}

// ToSlice returns all elements as slice
func (l *LinkedList) ToSlice() []string {
	result := make([]string, 0, l.size)
	current := l.head
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// MarshalJSON implements json.Marshaler
func (l *LinkedList) MarshalJSON() ([]byte, error) {
	return json.Marshal(l.ToSlice())
}

// UnmarshalJSON implements json.Unmarshaler
func (l *LinkedList) UnmarshalJSON(data []byte) error {
	var items []string
	if err := json.Unmarshal(data, &items); err != nil {
		return err
	}

	l.Clear()
	for _, item := range items {
		l.PushBack(item)
	}
	return nil
}
