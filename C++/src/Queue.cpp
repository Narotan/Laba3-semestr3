#include "../include/Queue.h"
#include <stdexcept>

Queue::Queue() : front(nullptr), back(nullptr), size(0) {}

Queue::Queue(const Queue &other) : front(nullptr), back(nullptr), size(0) {
  Node *current = other.front;
  while (current != nullptr) {
    enqueue(current->data);
    current = current->next;
  }
}

Queue::~Queue() { clear(); }

Queue &Queue::operator=(const Queue &other) {
  if (this != &other) {
    clear();
    Node *current = other.front;
    while (current != nullptr) {
      enqueue(current->data);
      current = current->next;
    }
  }
  return *this;
}

void Queue::enqueue(const std::string &value) {
  Node *newNode = new Node(value);
  if (back == nullptr) {
    front = back = newNode;
  } else {
    back->next = newNode;
    back = newNode;
  }
  size++;
}

std::string Queue::dequeue() {
  if (front == nullptr) {
    throw std::runtime_error("Queue is empty");
  }

  Node *temp = front;
  std::string value = front->data;
  front = front->next;

  if (front == nullptr) {
    back = nullptr;
  }

  delete temp;
  size--;
  return value;
}

std::string Queue::peek() const {
  if (front == nullptr) {
    throw std::runtime_error("Queue is empty");
  }
  return front->data;
}

void Queue::clear() {
  while (front != nullptr) {
    Node *temp = front;
    front = front->next;
    delete temp;
  }
  back = nullptr;
  size = 0;
}

void Queue::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  Node *current = front;
  while (current != nullptr) {
    int len = current->data.length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(current->data.c_str(), len);
    current = current->next;
  }
}

void Queue::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  for (int i = 0; i < newSize; i++) {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    char *buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    enqueue(std::string(buffer));
    delete[] buffer;
  }
}
