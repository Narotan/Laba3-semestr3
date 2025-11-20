#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <fstream>
#include <string>

class LinkedList {
private:
  struct Node {
    std::string data;
    Node *next;

    Node(const std::string &value) : data(value), next(nullptr) {}
  };

  Node *head;
  int size;

public:
  // Constructors and destructor
  LinkedList();
  LinkedList(const LinkedList &other);
  ~LinkedList();

  // Assignment operator
  LinkedList &operator=(const LinkedList &other);

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

#endif // LINKEDLIST_H
