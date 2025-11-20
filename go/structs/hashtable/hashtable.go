package hashtable

import (
	"encoding/json"
	"fmt"
)

// Node represents a hash table entry
type Node struct {
	Key   string
	Value string
	Next  *Node
}

// HashTable represents a hash table with chaining
type HashTable struct {
	buckets    []*Node
	capacity   int
	size       int
	loadFactor float64
}

// New creates a new HashTable
func New() *HashTable {
	capacity := 16
	return &HashTable{
		buckets:    make([]*Node, capacity),
		capacity:   capacity,
		size:       0,
		loadFactor: 0.75,
	}
}

// hash computes hash value for a key
func (ht *HashTable) hash(key string) int {
	hash := 5381
	for _, c := range key {
		hash = ((hash << 5) + hash) + int(c)
	}
	if hash < 0 {
		hash = -hash
	}
	return hash % ht.capacity
}

// Insert adds or updates a key-value pair
func (ht *HashTable) Insert(key, value string) {
	if float64(ht.size)/float64(ht.capacity) >= ht.loadFactor {
		ht.rehash()
	}

	index := ht.hash(key)
	current := ht.buckets[index]

	// Update if key exists
	for current != nil {
		if current.Key == key {
			current.Value = value
			return
		}
		current = current.Next
	}

	// Insert new node
	newNode := &Node{Key: key, Value: value, Next: ht.buckets[index]}
	ht.buckets[index] = newNode
	ht.size++
}

// Get retrieves value for a key
func (ht *HashTable) Get(key string) (string, error) {
	index := ht.hash(key)
	current := ht.buckets[index]

	for current != nil {
		if current.Key == key {
			return current.Value, nil
		}
		current = current.Next
	}

	return "", fmt.Errorf("key not found: %s", key)
}

// Contains checks if key exists
func (ht *HashTable) Contains(key string) bool {
	_, err := ht.Get(key)
	return err == nil
}

// Remove deletes a key-value pair
func (ht *HashTable) Remove(key string) {
	index := ht.hash(key)
	current := ht.buckets[index]
	var prev *Node

	for current != nil {
		if current.Key == key {
			if prev == nil {
				ht.buckets[index] = current.Next
			} else {
				prev.Next = current.Next
			}
			ht.size--
			return
		}
		prev = current
		current = current.Next
	}
}

// rehash doubles capacity and rehashes all entries
func (ht *HashTable) rehash() {
	oldBuckets := ht.buckets
	ht.capacity *= 2
	ht.buckets = make([]*Node, ht.capacity)
	ht.size = 0

	for _, bucket := range oldBuckets {
		current := bucket
		for current != nil {
			ht.Insert(current.Key, current.Value)
			current = current.Next
		}
	}
}

// Size returns number of entries
func (ht *HashTable) Size() int {
	return ht.size
}

// IsEmpty checks if table is empty
func (ht *HashTable) IsEmpty() bool {
	return ht.size == 0
}

// Clear removes all entries
func (ht *HashTable) Clear() {
	ht.buckets = make([]*Node, ht.capacity)
	ht.size = 0
}

// ToMap returns all entries as map
func (ht *HashTable) ToMap() map[string]string {
	result := make(map[string]string)
	for _, bucket := range ht.buckets {
		current := bucket
		for current != nil {
			result[current.Key] = current.Value
			current = current.Next
		}
	}
	return result
}

// MarshalJSON implements json.Marshaler
func (ht *HashTable) MarshalJSON() ([]byte, error) {
	return json.Marshal(ht.ToMap())
}

// UnmarshalJSON implements json.Unmarshaler
func (ht *HashTable) UnmarshalJSON(data []byte) error {
	var m map[string]string
	if err := json.Unmarshal(data, &m); err != nil {
		return err
	}

	ht.Clear()
	for k, v := range m {
		ht.Insert(k, v)
	}
	return nil
}
