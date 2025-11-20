#include "../include/DoubleLinkedList.h"
#include <stdexcept>

DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList &other)
    : head(nullptr), tail(nullptr), size(0) {
  Node *current = other.head;
  while (current != nullptr) {
    pushBack(current->data);
    current = current->next;
  }
}

DoubleLinkedList::~DoubleLinkedList() { clear(); }

DoubleLinkedList &DoubleLinkedList::operator=(const DoubleLinkedList &other) {
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

void DoubleLinkedList::pushFront(const std::string &value) {
  Node *newNode = new Node(value);
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  size++;
}

void DoubleLinkedList::pushBack(const std::string &value) {
  Node *newNode = new Node(value);
  if (tail == nullptr) {
    head = tail = newNode;
  } else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

void DoubleLinkedList::insert(int index, const std::string &value) {
  if (index < 0 || index > size) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    pushFront(value);
    return;
  }
  if (index == size) {
    pushBack(value);
    return;
  }

  Node *newNode = new Node(value);
  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  newNode->next = current;
  newNode->prev = current->prev;
  current->prev->next = newNode;
  current->prev = newNode;
  size++;
}

std::string DoubleLinkedList::get(int index) const {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }

  Node *current;
  if (index < size / 2) {
    current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
  } else {
    current = tail;
    for (int i = size - 1; i > index; i--) {
      current = current->prev;
    }
  }
  return current->data;
}

void DoubleLinkedList::set(int index, const std::string &value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }

  Node *current;
  if (index < size / 2) {
    current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
  } else {
    current = tail;
    for (int i = size - 1; i > index; i--) {
      current = current->prev;
    }
  }
  current->data = value;
}

void DoubleLinkedList::popFront() {
  if (head == nullptr) {
    throw std::runtime_error("List is empty");
  }

  Node *temp = head;
  head = head->next;
  if (head != nullptr) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }
  delete temp;
  size--;
}

void DoubleLinkedList::popBack() {
  if (tail == nullptr) {
    throw std::runtime_error("List is empty");
  }

  Node *temp = tail;
  tail = tail->prev;
  if (tail != nullptr) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }
  delete temp;
  size--;
}

void DoubleLinkedList::remove(int index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  if (index == 0) {
    popFront();
    return;
  }
  if (index == size - 1) {
    popBack();
    return;
  }

  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  current->prev->next = current->next;
  current->next->prev = current->prev;
  delete current;
  size--;
}

bool DoubleLinkedList::removeByValue(const std::string &value) {
  Node *current = head;
  while (current != nullptr) {
    if (current->data == value) {
      if (current == head) {
        popFront();
      } else if (current == tail) {
        popBack();
      } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
      }
      return true;
    }
    current = current->next;
  }
  return false;
}

void DoubleLinkedList::clear() {
  while (head != nullptr) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
  size = 0;
}

void DoubleLinkedList::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  Node *current = head;
  while (current != nullptr) {
    int len = current->data.length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(current->data.c_str(), len);
    current = current->next;
  }
}

void DoubleLinkedList::deserialize(std::ifstream &in) {
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
