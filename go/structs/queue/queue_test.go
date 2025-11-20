package queue

import (
	"encoding/json"
	"testing"
)

func TestQueueNew(t *testing.T) {
	q := New()
	if q.Size() != 0 {
		t.Errorf("Expected size 0, got %d", q.Size())
	}
	if !q.IsEmpty() {
		t.Error("Expected queue to be empty")
	}
}

func TestQueueEnqueue(t *testing.T) {
	q := New()
	q.Enqueue("first")
	q.Enqueue("second")
	q.Enqueue("third")

	if q.Size() != 3 {
		t.Errorf("Expected size 3, got %d", q.Size())
	}
}

func TestQueueDequeue(t *testing.T) {
	q := New()
	q.Enqueue("first")
	q.Enqueue("second")
	q.Enqueue("third")

	val, _ := q.Dequeue()
	if val != "first" {
		t.Errorf("Expected 'first', got '%s'", val)
	}

	if q.Size() != 2 {
		t.Errorf("Expected size 2, got %d", q.Size())
	}
}

func TestQueueFIFO(t *testing.T) {
	q := New()
	q.Enqueue("1")
	q.Enqueue("2")
	q.Enqueue("3")

	expected := []string{"1", "2", "3"}
	for _, exp := range expected {
		val, _ := q.Dequeue()
		if val != exp {
			t.Errorf("Expected '%s', got '%s'", exp, val)
		}
	}
}

func TestQueuePeek(t *testing.T) {
	q := New()
	q.Enqueue("first")
	q.Enqueue("second")

	val, _ := q.Peek()
	if val != "first" {
		t.Errorf("Expected 'first', got '%s'", val)
	}

	if q.Size() != 2 {
		t.Error("Peek should not remove element")
	}
}

func TestQueueSerialization(t *testing.T) {
	q := New()
	q.Enqueue("first")
	q.Enqueue("second")
	q.Enqueue("third")

	data, err := json.Marshal(q)
	if err != nil {
		t.Fatalf("Marshal error: %v", err)
	}

	q2 := New()
	err = json.Unmarshal(data, q2)
	if err != nil {
		t.Fatalf("Unmarshal error: %v", err)
	}

	val1, _ := q2.Dequeue()
	val2, _ := q2.Dequeue()
	val3, _ := q2.Dequeue()

	if val1 != "first" || val2 != "second" || val3 != "third" {
		t.Error("Queue order not preserved after serialization")
	}
}

func BenchmarkQueueEnqueue(b *testing.B) {
	q := New()
	for i := 0; i < b.N; i++ {
		q.Enqueue("test")
	}
}

func BenchmarkQueueDequeue(b *testing.B) {
	q := New()
	for i := 0; i < b.N; i++ {
		q.Enqueue("test")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		q.Dequeue()
	}
}
