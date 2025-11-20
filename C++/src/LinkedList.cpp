#include "../include/LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::LinkedList(const LinkedList &other) : head(nullptr), size(0) {
  Node *current = other.head;
  while (current != nullptr) {
    pushBack(current->data);
    current = current->next;
  }
}

LinkedList::~LinkedList() { clear(); }

LinkedList &LinkedList::operator=(const LinkedList &other) {
  if (this != &other) {
    clear();
    Node *current = other.head;
    while (current != nullptr) {
      pushBack(current->data);
      current = current->next;
    }
  }
  return *this;
}

void LinkedList::pushFront(const std::string &value) {
  Node *newNode = new Node(value);
  newNode->next = head;
  head = newNode;
  size++;
}

void LinkedList::pushBack(const std::string &value) {
  Node *newNode = new Node(value);
  if (head == nullptr) {
    head = newNode;
  } else {
    Node *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
  size++;
}

void LinkedList::insert(int index, const std::string &value) {
  if (index < 0 || index > size) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    pushFront(value);
    return;
  }

  Node *newNode = new Node(value);
  Node *current = head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }
  newNode->next = current->next;
  current->next = newNode;
  size++;
}

std::string LinkedList::get(int index) const {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current->data;
}

void LinkedList::set(int index, const std::string &value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  current->data = value;
}

void LinkedList::popFront() {
  if (head == nullptr) {
    throw std::runtime_error("List is empty");
  }
  Node *temp = head;
  head = head->next;
  delete temp;
  size--;
}

void LinkedList::popBack() {
  if (head == nullptr) {
    throw std::runtime_error("List is empty");
  }
  if (head->next == nullptr) {
    delete head;
    head = nullptr;
    size--;
    return;
  }

  Node *current = head;
  while (current->next->next != nullptr) {
    current = current->next;
  }
  delete current->next;
  current->next = nullptr;
  size--;
}

void LinkedList::remove(int index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    popFront();
    return;
  }

  Node *current = head;
  for (int i = 0; i < index - 1; i++) {
    current = current->next;
  }
  Node *temp = current->next;
  current->next = temp->next;
  delete temp;
  size--;
}

bool LinkedList::removeByValue(const std::string &value) {
  if (head == nullptr)
    return false;

  if (head->data == value) {
    popFront();
    return true;
  }

  Node *current = head;
  while (current->next != nullptr) {
    if (current->next->data == value) {
      Node *temp = current->next;
      current->next = temp->next;
      delete temp;
      size--;
      return true;
    }
    current = current->next;
  }
  return false;
}

void LinkedList::clear() {
  while (head != nullptr) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  size = 0;
}

void LinkedList::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  Node *current = head;
  while (current != nullptr) {
    int len = current->data.length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(current->data.c_str(), len);
    current = current->next;
  }
}

void LinkedList::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  for (int i = 0; i < newSize; i++) {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    char *buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    pushBack(std::string(buffer));
    delete[] buffer;
  }
}
