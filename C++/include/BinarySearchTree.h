#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <fstream>
#include <string>

class BinarySearchTree {
private:
  struct Node {
    std::string data;
    Node *left;
    Node *right;

    Node(const std::string &value)
        : data(value), left(nullptr), right(nullptr) {}
  };

  Node *root;
  int size;

  // Helper methods
  Node *insertHelper(Node *node, const std::string &value);
  Node *removeHelper(Node *node, const std::string &value);
  Node *findMin(Node *node) const;
  bool searchHelper(Node *node, const std::string &value) const;
  void clearHelper(Node *node);
  Node *copyHelper(const Node *node);
  void serializeHelper(Node *node, std::ofstream &out) const;

public:
  // Constructors and destructor
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &other);
  ~BinarySearchTree();

  // Assignment operator
  BinarySearchTree &operator=(const BinarySearchTree &other);

  // Basic operations
  void insert(const std::string &value);
  void remove(const std::string &value);
  bool search(const std::string &value) const;

  // Utility methods
  int getSize() const { return size; }
  bool empty() const { return size == 0; }
  void clear();

  // Serialization
  void serialize(std::ofstream &out) const;
  void deserialize(std::ifstream &in);
};

#endif // BINARYSEARCHTREE_H
