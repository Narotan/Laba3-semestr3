#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <fstream>
#include <string>

class DoubleLinkedList {
private:
  struct Node {
    std::string data;
    Node *next;
    Node *prev;

    Node(const std::string &value)
        : data(value), next(nullptr), prev(nullptr) {}
  };

  Node *head;
  Node *tail;
  int size;

public:
  // Constructors and destructor
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList &other);
  ~DoubleLinkedList();

  // Assignment operator
  DoubleLinkedList &operator=(const DoubleLinkedList &other);

  // Basic operations
  void pushFront(const std::string &value);
  void pushBack(const std::string &value);
  void insert(int index, const std::string &value);
  std::string get(int index) const;
  void set(int index, const std::string &value);
  void popFront();
  void popBack();
  void remove(int index);
  bool removeByValue(const std::string &value);

  // Utility methods
  int getSize() const { return size; }
  bool empty() const { return size == 0; }
  void clear();

  // Serialization
  void serialize(std::ofstream &out) const;
  void deserialize(std::ifstream &in);
};

#endif // DOUBLELINKEDLIST_H
