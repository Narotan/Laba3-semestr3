#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <fstream>
#include <string>

class HashTable {
private:
  struct Node {
    std::string key;
    std::string value;
    Node *next;

    Node(const std::string &k, const std::string &v)
        : key(k), value(v), next(nullptr) {}
  };

  Node **buckets;
  int capacity;
  int size;
  float loadFactor;

  int hash(const std::string &key) const;
  void rehash();

public:
  // Constructors and destructor
  HashTable();
  HashTable(int initialCapacity);
  HashTable(const HashTable &other);
  ~HashTable();

  // Assignment operator
  HashTable &operator=(const HashTable &other);

  // Basic operations
  void insert(const std::string &key, const std::string &value);
  std::string get(const std::string &key) const;
  bool contains(const std::string &key) const;
  void remove(const std::string &key);

  // Utility methods
  int getSize() const { return size; }
  int getCapacity() const { return capacity; }
  bool empty() const { return size == 0; }
  void clear();

  // Serialization
  void serialize(std::ofstream &out) const;
  void deserialize(std::ifstream &in);
};

#endif // HASHTABLE_H
