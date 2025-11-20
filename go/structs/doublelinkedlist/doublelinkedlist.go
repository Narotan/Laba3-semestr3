package doublelinkedlist

import (
	"encoding/json"
	"fmt"
)

// Node represents a doubly linked list node
type Node struct {
	Data string
	Next *Node
	Prev *Node
}

// DoubleLinkedList represents a doubly linked list
type DoubleLinkedList struct {
	head *Node
	tail *Node
	size int
}

// New creates a new DoubleLinkedList
func New() *DoubleLinkedList {
	return &DoubleLinkedList{}
}

// PushFront adds an element to the front
func (l *DoubleLinkedList) PushFront(value string) {
	newNode := &Node{Data: value}

	if l.head == nil {
		l.head = newNode
		l.tail = newNode
	} else {
		newNode.Next = l.head
		l.head.Prev = newNode
		l.head = newNode
	}
	l.size++
}

// PushBack adds an element to the back
func (l *DoubleLinkedList) PushBack(value string) {
	newNode := &Node{Data: value}

	if l.tail == nil {
		l.head = newNode
		l.tail = newNode
	} else {
		newNode.Prev = l.tail
		l.tail.Next = newNode
		l.tail = newNode
	}
	l.size++
}

// PopFront removes the first element
func (l *DoubleLinkedList) PopFront() error {
	if l.head == nil {
		return fmt.Errorf("list is empty")
	}

	l.head = l.head.Next
	if l.head != nil {
		l.head.Prev = nil
	} else {
		l.tail = nil
	}
	l.size--
	return nil
}

// PopBack removes the last element
func (l *DoubleLinkedList) PopBack() error {
	if l.tail == nil {
		return fmt.Errorf("list is empty")
	}

	l.tail = l.tail.Prev
	if l.tail != nil {
		l.tail.Next = nil
	} else {
		l.head = nil
	}
	l.size--
	return nil
}

// Get returns element at index (optimized for bidirectional access)
func (l *DoubleLinkedList) Get(index int) (string, error) {
	if index < 0 || index >= l.size {
		return "", fmt.Errorf("index out of range: %d", index)
	}

	var current *Node
	if index < l.size/2 {
		current = l.head
		for i := 0; i < index; i++ {
			current = current.Next
		}
	} else {
		current = l.tail
		for i := l.size - 1; i > index; i-- {
			current = current.Prev
		}
	}
	return current.Data, nil
}

// Size returns the number of elements
func (l *DoubleLinkedList) Size() int {
	return l.size
}

// IsEmpty checks if list is empty
func (l *DoubleLinkedList) IsEmpty() bool {
	return l.size == 0
}

// Clear removes all elements
func (l *DoubleLinkedList) Clear() {
	l.head = nil
	l.tail = nil
	l.size = 0
}

// ToSlice returns all elements as slice
func (l *DoubleLinkedList) ToSlice() []string {
	result := make([]string, 0, l.size)
	current := l.head
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// MarshalJSON implements json.Marshaler
func (l *DoubleLinkedList) MarshalJSON() ([]byte, error) {
	return json.Marshal(l.ToSlice())
}

// UnmarshalJSON implements json.Unmarshaler
func (l *DoubleLinkedList) UnmarshalJSON(data []byte) error {
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
