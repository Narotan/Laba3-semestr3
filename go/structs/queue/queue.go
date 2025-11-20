package queue

import (
	"encoding/json"
	"fmt"
)

// Node represents a queue node
type Node struct {
	Data string
	Next *Node
}

// Queue represents a FIFO data structure
type Queue struct {
	front *Node
	back  *Node
	size  int
}

// New creates a new Queue
func New() *Queue {
	return &Queue{
		front: nil,
		back:  nil,
		size:  0,
	}
}

// Enqueue adds an element to the back
func (q *Queue) Enqueue(value string) {
	newNode := &Node{
		Data: value,
		Next: nil,
	}

	if q.back == nil {
		q.front = newNode
		q.back = newNode
	} else {
		q.back.Next = newNode
		q.back = newNode
	}
	q.size++
}

// Dequeue removes and returns the front element
func (q *Queue) Dequeue() (string, error) {
	if q.front == nil {
		return "", fmt.Errorf("queue is empty")
	}

	value := q.front.Data
	q.front = q.front.Next

	if q.front == nil {
		q.back = nil
	}

	q.size--
	return value, nil
}

// Peek returns the front element without removing it
func (q *Queue) Peek() (string, error) {
	if q.front == nil {
		return "", fmt.Errorf("queue is empty")
	}
	return q.front.Data, nil
}

// Size returns the number of elements
func (q *Queue) Size() int {
	return q.size
}

// IsEmpty checks if queue is empty
func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

// Clear removes all elements
func (q *Queue) Clear() {
	q.front = nil
	q.back = nil
	q.size = 0
}

// ToSlice returns all elements as slice (front to back)
func (q *Queue) ToSlice() []string {
	result := make([]string, 0, q.size)
	current := q.front
	for current != nil {
		result = append(result, current.Data)
		current = current.Next
	}
	return result
}

// MarshalJSON implements json.Marshaler
func (q *Queue) MarshalJSON() ([]byte, error) {
	return json.Marshal(q.ToSlice())
}

// UnmarshalJSON implements json.Unmarshaler
func (q *Queue) UnmarshalJSON(data []byte) error {
	var items []string
	if err := json.Unmarshal(data, &items); err != nil {
		return err
	}

	q.Clear()
	for _, item := range items {
		q.Enqueue(item)
	}
	return nil
}
