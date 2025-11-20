#include "include/Array.h"
#include "include/BinarySearchTree.h"
#include "include/DoubleLinkedList.h"
#include "include/HashTable.h"
#include "include/LinkedList.h"
#include "include/Queue.h"
#include "include/Stack.h"
#include <fstream>
#include <iostream>

void demonstrateArray() {
  std::cout << "\n=== Array Demo ===" << std::endl;
  Array arr;
  arr.append("Hello");
  arr.append("World");
  arr.append("C++");

  std::cout << "Size: " << arr.getSize() << std::endl;
  std::cout << "Elements: ";
  for (int i = 0; i < arr.getSize(); i++) {
    std::cout << arr.get(i) << " ";
  }
  std::cout << std::endl;

  // Serialization test
  std::ofstream out("array.bin", std::ios::binary);
  arr.serialize(out);
  out.close();

  Array arr2;
  std::ifstream in("array.bin", std::ios::binary);
  arr2.deserialize(in);
  in.close();

  std::cout << "After deserialization: ";
  for (int i = 0; i < arr2.getSize(); i++) {
    std::cout << arr2.get(i) << " ";
  }
  std::cout << std::endl;
}

void demonstrateLinkedList() {
  std::cout << "\n=== LinkedList Demo ===" << std::endl;
  LinkedList list;
  list.pushBack("Node1");
  list.pushBack("Node2");
  list.pushFront("Node0");

  std::cout << "Size: " << list.getSize() << std::endl;
  std::cout << "Elements: ";
  for (int i = 0; i < list.getSize(); i++) {
    std::cout << list.get(i) << " ";
  }
  std::cout << std::endl;
}

void demonstrateQueue() {
  std::cout << "\n=== Queue Demo ===" << std::endl;
  Queue queue;
  queue.enqueue("First");
  queue.enqueue("Second");
  queue.enqueue("Third");

  std::cout << "Front: " << queue.peek() << std::endl;
  std::cout << "Dequeue: " << queue.dequeue() << std::endl;
  std::cout << "New front: " << queue.peek() << std::endl;
}

void demonstrateStack() {
  std::cout << "\n=== Stack Demo ===" << std::endl;
  Stack stack;
  stack.push("Bottom");
  stack.push("Middle");
  stack.push("Top");

  std::cout << "Top: " << stack.peek() << std::endl;
  std::cout << "Pop: " << stack.pop() << std::endl;
  std::cout << "New top: " << stack.peek() << std::endl;
}

void demonstrateHashTable() {
  std::cout << "\n=== HashTable Demo ===" << std::endl;
  HashTable ht;
  ht.insert("name", "John");
  ht.insert("age", "25");
  ht.insert("city", "Moscow");

  std::cout << "Name: " << ht.get("name") << std::endl;
  std::cout << "Age: " << ht.get("age") << std::endl;
  std::cout << "Contains 'city': " << (ht.contains("city") ? "Yes" : "No")
            << std::endl;
}

void demonstrateBST() {
  std::cout << "\n=== Binary Search Tree Demo ===" << std::endl;
  BinarySearchTree bst;
  bst.insert("dog");
  bst.insert("cat");
  bst.insert("elephant");
  bst.insert("ant");

  std::cout << "Size: " << bst.getSize() << std::endl;
  std::cout << "Search 'cat': " << (bst.search("cat") ? "Found" : "Not found")
            << std::endl;
  std::cout << "Search 'bird': " << (bst.search("bird") ? "Found" : "Not found")
            << std::endl;

  bst.remove("cat");
  std::cout << "After removing 'cat', size: " << bst.getSize() << std::endl;
}

int main() {
  std::cout << "Laboratory Work #3 - OOP Data Structures" << std::endl;
  std::cout << "===========================================" << std::endl;

  try {
    demonstrateArray();
    demonstrateLinkedList();
    demonstrateQueue();
    demonstrateStack();
    demonstrateHashTable();
    demonstrateBST();

    std::cout << "\n=== All demonstrations completed successfully ==="
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
