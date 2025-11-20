#ifndef STACK_H
#define STACK_H

#include <fstream>
#include <string>

class Stack {
private:
  struct Node {
    std::string data;
    Node *next;

    Node(const std::string &value) : data(value), next(nullptr) {}
  };

  Node *top;
  int size;

public:
  // Constructors and destructor
  Stack();
  Stack(const Stack &other);
  ~Stack();

  // Assignment operator
  Stack &operator=(const Stack &other);

  // Basic operations
  void push(const std::string &value);
  std::string pop();
  std::string peek() const;

  // Utility methods
  int getSize() const { return size; }
  bool empty() const { return size == 0; }
  void clear();

  // Serialization
  void serialize(std::ofstream &out) const;
  void deserialize(std::ifstream &in);
};

#endif // STACK_H
