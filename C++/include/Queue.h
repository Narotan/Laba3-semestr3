#ifndef QUEUE_H
#define QUEUE_H

#include <fstream>
#include <string>

class Queue {
private:
  struct Node {
    std::string data;
    Node *next;

    Node(const std::string &value) : data(value), next(nullptr) {}
  };

  Node *front;
  Node *back;
  int size;

public:
  // Constructors and destructor
  Queue();
  Queue(const Queue &other);
  ~Queue();

  // Assignment operator
  Queue &operator=(const Queue &other);

  // Basic operations
  void enqueue(const std::string &value);
  std::string dequeue();
  std::string peek() const;

  // Utility methods
  int getSize() const { return size; }
  bool empty() const { return size == 0; }
  void clear();

  // Serialization
  void serialize(std::ofstream &out) const;
  void deserialize(std::ifstream &in);
};

#endif // QUEUE_H
