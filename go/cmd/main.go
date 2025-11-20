package main

import (
	"encoding/json"
	"fmt"
	"laba3/structs/array"
	"laba3/structs/bst"
	"laba3/structs/hashtable"
	"laba3/structs/linkedlist"
	"laba3/structs/queue"
	"laba3/structs/stack"
	"os"
)

func demonstrateArray() {
	fmt.Println("\n=== Array Demo ===")
	arr := array.New()
	arr.Append("Hello")
	arr.Append("World")
	arr.Append("Go")

	fmt.Printf("Size: %d\n", arr.Size())
	fmt.Print("Elements: ")
	for i := 0; i < arr.Size(); i++ {
		val, _ := arr.Get(i)
		fmt.Printf("%s ", val)
	}
	fmt.Println()

	// JSON Serialization
	data, _ := json.MarshalIndent(arr, "", "  ")
	fmt.Printf("Serialized: %s\n", string(data))
}

func demonstrateStack() {
	fmt.Println("\n=== Stack Demo ===")
	s := stack.New()
	s.Push("Bottom")
	s.Push("Middle")
	s.Push("Top")

	fmt.Printf("Top: %s\n", mustGet(s.Peek()))
	fmt.Printf("Pop: %s\n", mustGet(s.Pop()))
	fmt.Printf("New top: %s\n", mustGet(s.Peek()))
}

func demonstrateQueue() {
	fmt.Println("\n=== Queue Demo ===")
	q := queue.New()
	q.Enqueue("First")
	q.Enqueue("Second")
	q.Enqueue("Third")

	fmt.Printf("Front: %s\n", mustGet(q.Peek()))
	fmt.Printf("Dequeue: %s\n", mustGet(q.Dequeue()))
	fmt.Printf("New front: %s\n", mustGet(q.Peek()))
}

func demonstrateLinkedList() {
	fmt.Println("\n=== LinkedList Demo ===")
	list := linkedlist.New()
	list.PushBack("Node1")
	list.PushBack("Node2")
	list.PushFront("Node0")

	fmt.Printf("Size: %d\n", list.Size())
	fmt.Print("Elements: ")
	for i := 0; i < list.Size(); i++ {
		val, _ := list.Get(i)
		fmt.Printf("%s ", val)
	}
	fmt.Println()
}

func demonstrateHashTable() {
	fmt.Println("\n=== HashTable Demo ===")
	ht := hashtable.New()
	ht.Insert("name", "Ivan")
	ht.Insert("age", "22")
	ht.Insert("city", "Moscow")

	fmt.Printf("Name: %s\n", mustGet(ht.Get("name")))
	fmt.Printf("Age: %s\n", mustGet(ht.Get("age")))
	fmt.Printf("Contains 'city': %t\n", ht.Contains("city"))
}

func demonstrateBST() {
	fmt.Println("\n=== Binary Search Tree Demo ===")
	bst := bst.New()
	bst.Insert("dog")
	bst.Insert("cat")
	bst.Insert("elephant")
	bst.Insert("ant")

	fmt.Printf("Size: %d\n", bst.Size())
	fmt.Printf("Search 'cat': %t\n", bst.Search("cat"))
	fmt.Printf("Search 'bird': %t\n", bst.Search("bird"))

	bst.Remove("cat")
	fmt.Printf("After removing 'cat', size: %d\n", bst.Size())

	fmt.Print("In-order traversal: ")
	for _, val := range bst.InOrder() {
		fmt.Printf("%s ", val)
	}
	fmt.Println()
}

func demonstrateSerialization() {
	fmt.Println("\n=== Serialization Demo ===")

	arr := array.New()
	arr.Append("test1")
	arr.Append("test2")

	// Save to file
	data, _ := json.MarshalIndent(arr, "", "  ")
	os.WriteFile("array_data.json", data, 0644)
	fmt.Println("Saved array to array_data.json")

	// Load from file
	fileData, _ := os.ReadFile("array_data.json")
	arr2 := array.New()
	json.Unmarshal(fileData, arr2)
	fmt.Printf("Loaded array size: %d\n", arr2.Size())
}

func mustGet(val string, err error) string {
	if err != nil {
		return fmt.Sprintf("Error: %v", err)
	}
	return val
}

func main() {
	fmt.Println("Laboratory Work #3 - OOP Data Structures (Go)")
	fmt.Println("===============================================")

	demonstrateArray()
	demonstrateStack()
	demonstrateQueue()
	demonstrateLinkedList()
	demonstrateHashTable()
	demonstrateBST()
	demonstrateSerialization()

	fmt.Println("\n=== All demonstrations completed successfully ===")
}
