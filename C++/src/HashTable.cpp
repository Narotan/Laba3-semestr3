#include "../include/HashTable.h"
#include <stdexcept>

HashTable::HashTable()
    : buckets(nullptr), capacity(16), size(0), loadFactor(0.75f) {
  buckets = new Node *[capacity];
  for (int i = 0; i < capacity; i++) {
    buckets[i] = nullptr;
  }
}

HashTable::HashTable(int initialCapacity)
    : buckets(nullptr), capacity(initialCapacity), size(0), loadFactor(0.75f) {
  if (capacity <= 0) {
    capacity = 16;
  }
  buckets = new Node *[capacity];
  for (int i = 0; i < capacity; i++) {
    buckets[i] = nullptr;
  }
}

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), size(0), loadFactor(other.loadFactor) {
  buckets = new Node *[capacity];
  for (int i = 0; i < capacity; i++) {
    buckets[i] = nullptr;
  }

  for (int i = 0; i < other.capacity; i++) {
    Node *current = other.buckets[i];
    while (current != nullptr) {
      insert(current->key, current->value);
      current = current->next;
    }
  }
}

HashTable::~HashTable() {
  clear();
  delete[] buckets;
}

HashTable &HashTable::operator=(const HashTable &other) {
  if (this != &other) {
    clear();
    delete[] buckets;

    capacity = other.capacity;
    loadFactor = other.loadFactor;
    size = 0;

    buckets = new Node *[capacity];
    for (int i = 0; i < capacity; i++) {
      buckets[i] = nullptr;
    }

    for (int i = 0; i < other.capacity; i++) {
      Node *current = other.buckets[i];
      while (current != nullptr) {
        insert(current->key, current->value);
        current = current->next;
      }
    }
  }
  return *this;
}

int HashTable::hash(const std::string &key) const {
  unsigned long hash = 5381;
  for (char c : key) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  return hash % capacity;
}

void HashTable::rehash() {
  int oldCapacity = capacity;
  Node **oldBuckets = buckets;

  capacity *= 2;
  buckets = new Node *[capacity];
  for (int i = 0; i < capacity; i++) {
    buckets[i] = nullptr;
  }

  int oldSize = size;
  size = 0;

  for (int i = 0; i < oldCapacity; i++) {
    Node *current = oldBuckets[i];
    while (current != nullptr) {
      insert(current->key, current->value);
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }

  delete[] oldBuckets;
}

void HashTable::insert(const std::string &key, const std::string &value) {
  if ((float)size / capacity >= loadFactor) {
    rehash();
  }

  int index = hash(key);
  Node *current = buckets[index];

  // Update if key exists
  while (current != nullptr) {
    if (current->key == key) {
      current->value = value;
      return;
    }
    current = current->next;
  }

  // Insert new node
  Node *newNode = new Node(key, value);
  newNode->next = buckets[index];
  buckets[index] = newNode;
  size++;
}

std::string HashTable::get(const std::string &key) const {
  int index = hash(key);
  Node *current = buckets[index];

  while (current != nullptr) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  throw std::runtime_error("Key not found");
}

bool HashTable::contains(const std::string &key) const {
  int index = hash(key);
  Node *current = buckets[index];

  while (current != nullptr) {
    if (current->key == key) {
      return true;
    }
    current = current->next;
  }
  return false;
}

void HashTable::remove(const std::string &key) {
  int index = hash(key);
  Node *current = buckets[index];
  Node *prev = nullptr;

  while (current != nullptr) {
    if (current->key == key) {
      if (prev == nullptr) {
        buckets[index] = current->next;
      } else {
        prev->next = current->next;
      }
      delete current;
      size--;
      return;
    }
    prev = current;
    current = current->next;
  }
}

void HashTable::clear() {
  for (int i = 0; i < capacity; i++) {
    Node *current = buckets[i];
    while (current != nullptr) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
    buckets[i] = nullptr;
  }
  size = 0;
}

void HashTable::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));

  for (int i = 0; i < capacity; i++) {
    Node *current = buckets[i];
    while (current != nullptr) {
      int keyLen = current->key.length();
      int valLen = current->value.length();

      out.write(reinterpret_cast<const char *>(&keyLen), sizeof(keyLen));
      out.write(current->key.c_str(), keyLen);

      out.write(reinterpret_cast<const char *>(&valLen), sizeof(valLen));
      out.write(current->value.c_str(), valLen);

      current = current->next;
    }
  }
}

void HashTable::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  for (int i = 0; i < newSize; i++) {
    int keyLen, valLen;

    in.read(reinterpret_cast<char *>(&keyLen), sizeof(keyLen));
    char *keyBuffer = new char[keyLen + 1];
    in.read(keyBuffer, keyLen);
    keyBuffer[keyLen] = '\0';

    in.read(reinterpret_cast<char *>(&valLen), sizeof(valLen));
    char *valBuffer = new char[valLen + 1];
    in.read(valBuffer, valLen);
    valBuffer[valLen] = '\0';

    insert(std::string(keyBuffer), std::string(valBuffer));

    delete[] keyBuffer;
    delete[] valBuffer;
  }
}
