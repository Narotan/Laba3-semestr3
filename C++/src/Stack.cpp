#include "../include/Stack.h"
#include <stdexcept>

Stack::Stack() : top(nullptr), size(0) {}

Stack::Stack(const Stack &other) : top(nullptr), size(0) {
  if (other.top == nullptr)
    return;

  // Build reversed copy first
  Node *current = other.top;
  Stack temp;
  while (current != nullptr) {
    temp.push(current->data);
    current = current->next;
  }

  // Copy from temp to this in correct order
  current = temp.top;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

Stack::~Stack() { clear(); }

Stack &Stack::operator=(const Stack &other) {
  if (this != &other) {
    clear();
    if (other.top != nullptr) {
      // Build reversed copy first
      Node *current = other.top;
      Stack temp;
      while (current != nullptr) {
        temp.push(current->data);
        current = current->next;
      }

      // Copy from temp to this in correct order
      current = temp.top;
      while (current != nullptr) {
        push(current->data);
        current = current->next;
      }
    }
  }
  return *this;
}

void Stack::push(const std::string &value) {
  Node *newNode = new Node(value);
  newNode->next = top;
  top = newNode;
  size++;
}

std::string Stack::pop() {
  if (top == nullptr) {
    throw std::runtime_error("Stack is empty");
  }

  Node *temp = top;
  std::string value = top->data;
  top = top->next;
  delete temp;
  size--;
  return value;
}

std::string Stack::peek() const {
  if (top == nullptr) {
    throw std::runtime_error("Stack is empty");
  }
  return top->data;
}

void Stack::clear() {
  while (top != nullptr) {
    Node *temp = top;
    top = top->next;
    delete temp;
  }
  size = 0;
}

void Stack::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  Node *current = top;
  while (current != nullptr) {
    int len = current->data.length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(current->data.c_str(), len);
    current = current->next;
  }
}

void Stack::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  // Read into temporary array to preserve order
  std::string *items = new std::string[newSize];
  for (int i = 0; i < newSize; i++) {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    char *buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    items[i] = std::string(buffer);
    delete[] buffer;
  }

  // Push in reverse order to maintain stack order
  for (int i = newSize - 1; i >= 0; i--) {
    push(items[i]);
  }
  delete[] items;
}
