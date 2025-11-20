package bst

import (
	"encoding/json"
	"fmt"
)

// Node represents a BST node
type Node struct {
	Data  string
	Left  *Node
	Right *Node
}

// BinarySearchTree represents a binary search tree
type BinarySearchTree struct {
	root *Node
	size int
}

// New creates a new BinarySearchTree
func New() *BinarySearchTree {
	return &BinarySearchTree{}
}

// Insert adds a value to the tree
func (bst *BinarySearchTree) Insert(value string) {
	bst.root = bst.insertHelper(bst.root, value)
}

func (bst *BinarySearchTree) insertHelper(node *Node, value string) *Node {
	if node == nil {
		bst.size++
		return &Node{Data: value}
	}

	if value < node.Data {
		node.Left = bst.insertHelper(node.Left, value)
	} else if value > node.Data {
		node.Right = bst.insertHelper(node.Right, value)
	}
	// Don't insert duplicates

	return node
}

// Search checks if a value exists
func (bst *BinarySearchTree) Search(value string) bool {
	return bst.searchHelper(bst.root, value)
}

func (bst *BinarySearchTree) searchHelper(node *Node, value string) bool {
	if node == nil {
		return false
	}

	if value == node.Data {
		return true
	} else if value < node.Data {
		return bst.searchHelper(node.Left, value)
	} else {
		return bst.searchHelper(node.Right, value)
	}
}

// Remove deletes a value from the tree
func (bst *BinarySearchTree) Remove(value string) {
	bst.root = bst.removeHelper(bst.root, value)
}

func (bst *BinarySearchTree) removeHelper(node *Node, value string) *Node {
	if node == nil {
		return nil
	}

	if value < node.Data {
		node.Left = bst.removeHelper(node.Left, value)
	} else if value > node.Data {
		node.Right = bst.removeHelper(node.Right, value)
	} else {
		// Node found
		if node.Left == nil && node.Right == nil {
			bst.size--
			return nil
		} else if node.Left == nil {
			bst.size--
			return node.Right
		} else if node.Right == nil {
			bst.size--
			return node.Left
		} else {
			// Two children
			minRight := bst.findMin(node.Right)
			node.Data = minRight.Data
			node.Right = bst.removeHelper(node.Right, minRight.Data)
			bst.size++
		}
	}

	return node
}

func (bst *BinarySearchTree) findMin(node *Node) *Node {
	for node.Left != nil {
		node = node.Left
	}
	return node
}

// Size returns number of nodes
func (bst *BinarySearchTree) Size() int {
	return bst.size
}

// IsEmpty checks if tree is empty
func (bst *BinarySearchTree) IsEmpty() bool {
	return bst.size == 0
}

// Clear removes all nodes
func (bst *BinarySearchTree) Clear() {
	bst.root = nil
	bst.size = 0
}

// InOrder returns values in sorted order
func (bst *BinarySearchTree) InOrder() []string {
	result := []string{}
	bst.inOrderHelper(bst.root, &result)
	return result
}

func (bst *BinarySearchTree) inOrderHelper(node *Node, result *[]string) {
	if node != nil {
		bst.inOrderHelper(node.Left, result)
		*result = append(*result, node.Data)
		bst.inOrderHelper(node.Right, result)
	}
}

// MarshalJSON implements json.Marshaler
func (bst *BinarySearchTree) MarshalJSON() ([]byte, error) {
	type SerializedBST struct {
		Values []string `json:"values"`
	}
	return json.Marshal(SerializedBST{Values: bst.InOrder()})
}

// UnmarshalJSON implements json.Unmarshaler
func (bst *BinarySearchTree) UnmarshalJSON(data []byte) error {
	type SerializedBST struct {
		Values []string `json:"values"`
	}

	var s SerializedBST
	if err := json.Unmarshal(data, &s); err != nil {
		return fmt.Errorf("unmarshal error: %w", err)
	}

	bst.Clear()
	for _, value := range s.Values {
		bst.Insert(value)
	}
	return nil
}
