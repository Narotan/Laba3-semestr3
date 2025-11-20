#include "../include/BinarySearchTree.h"
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root(nullptr), size(0) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other)
    : root(nullptr), size(0) {
  root = copyHelper(other.root);
  size = other.size;
}

BinarySearchTree::~BinarySearchTree() { clear(); }

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other) {
  if (this != &other) {
    clear();
    root = copyHelper(other.root);
    size = other.size;
  }
  return *this;
}

BinarySearchTree::Node *BinarySearchTree::copyHelper(const Node *node) {
  if (node == nullptr) {
    return nullptr;
  }

  Node *newNode = new Node(node->data);
  newNode->left = copyHelper(node->left);
  newNode->right = copyHelper(node->right);
  return newNode;
}

BinarySearchTree::Node *
BinarySearchTree::insertHelper(Node *node, const std::string &value) {
  if (node == nullptr) {
    size++;
    return new Node(value);
  }

  if (value < node->data) {
    node->left = insertHelper(node->left, value);
  } else if (value > node->data) {
    node->right = insertHelper(node->right, value);
  }
  // If value == node->data, don't insert duplicate

  return node;
}

BinarySearchTree::Node *BinarySearchTree::findMin(Node *node) const {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

BinarySearchTree::Node *
BinarySearchTree::removeHelper(Node *node, const std::string &value) {
  if (node == nullptr) {
    return nullptr;
  }

  if (value < node->data) {
    node->left = removeHelper(node->left, value);
  } else if (value > node->data) {
    node->right = removeHelper(node->right, value);
  } else {
    // Node found
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      size--;
      return nullptr;
    } else if (node->left == nullptr) {
      Node *temp = node->right;
      delete node;
      size--;
      return temp;
    } else if (node->right == nullptr) {
      Node *temp = node->left;
      delete node;
      size--;
      return temp;
    } else {
      // Node has two children
      Node *minRight = findMin(node->right);
      node->data = minRight->data;
      node->right = removeHelper(node->right, minRight->data);
      size++; // Compensate for decrement in recursive call
    }
  }

  return node;
}

bool BinarySearchTree::searchHelper(Node *node,
                                    const std::string &value) const {
  if (node == nullptr) {
    return false;
  }

  if (value == node->data) {
    return true;
  } else if (value < node->data) {
    return searchHelper(node->left, value);
  } else {
    return searchHelper(node->right, value);
  }
}

void BinarySearchTree::clearHelper(Node *node) {
  if (node != nullptr) {
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
  }
}

void BinarySearchTree::insert(const std::string &value) {
  root = insertHelper(root, value);
}

void BinarySearchTree::remove(const std::string &value) {
  root = removeHelper(root, value);
}

bool BinarySearchTree::search(const std::string &value) const {
  return searchHelper(root, value);
}

void BinarySearchTree::clear() {
  clearHelper(root);
  root = nullptr;
  size = 0;
}

void BinarySearchTree::serializeHelper(Node *node, std::ofstream &out) const {
  if (node == nullptr) {
    int nullMarker = -1;
    out.write(reinterpret_cast<const char *>(&nullMarker), sizeof(nullMarker));
    return;
  }

  int len = node->data.length();
  out.write(reinterpret_cast<const char *>(&len), sizeof(len));
  out.write(node->data.c_str(), len);

  serializeHelper(node->left, out);
  serializeHelper(node->right, out);
}

void BinarySearchTree::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  serializeHelper(root, out);
}

void BinarySearchTree::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  // Helper lambda for recursive deserialization
  std::function<Node *()> deserializeHelper = [&]() -> Node * {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));

    if (len == -1) {
      return nullptr;
    }

    char *buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';

    Node *node = new Node(std::string(buffer));
    delete[] buffer;

    node->left = deserializeHelper();
    node->right = deserializeHelper();

    return node;
  };

  root = deserializeHelper();
  size = newSize;
}
