#include "../include/Array.h"
#include <cstring>
#include <stdexcept>

Array::Array() : data(nullptr), size(0), capacity(10) {
  data = new std::string[capacity];
}

Array::Array(int initialCapacity)
    : data(nullptr), size(0), capacity(initialCapacity) {
  if (capacity <= 0) {
    capacity = 10;
  }
  data = new std::string[capacity];
}

Array::Array(const Array &other) : size(other.size), capacity(other.capacity) {
  data = new std::string[capacity];
  for (int i = 0; i < size; i++) {
    data[i] = other.data[i];
  }
}

Array::~Array() { delete[] data; }

Array &Array::operator=(const Array &other) {
  if (this != &other) {
    delete[] data;
    size = other.size;
    capacity = other.capacity;
    data = new std::string[capacity];
    for (int i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
  }
  return *this;
}

void Array::resize() {
  capacity *= 2;
  std::string *newData = new std::string[capacity];
  for (int i = 0; i < size; i++) {
    newData[i] = data[i];
  }
  delete[] data;
  data = newData;
}

void Array::append(const std::string &value) {
  if (size >= capacity) {
    resize();
  }
  data[size++] = value;
}

void Array::insert(int index, const std::string &value) {
  if (index < 0 || index > size) {
    throw std::out_of_range("Index out of range");
  }
  if (size >= capacity) {
    resize();
  }
  for (int i = size; i > index; i--) {
    data[i] = data[i - 1];
  }
  data[index] = value;
  size++;
}

std::string Array::get(int index) const {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

void Array::set(int index, const std::string &value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  data[index] = value;
}

void Array::remove(int index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
  }
  for (int i = index; i < size - 1; i++) {
    data[i] = data[i + 1];
  }
  size--;
}

bool Array::removeByValue(const std::string &value) {
  for (int i = 0; i < size; i++) {
    if (data[i] == value) {
      remove(i);
      return true;
    }
  }
  return false;
}

void Array::clear() { size = 0; }

void Array::serialize(std::ofstream &out) const {
  out.write(reinterpret_cast<const char *>(&size), sizeof(size));
  for (int i = 0; i < size; i++) {
    int len = data[i].length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(data[i].c_str(), len);
  }
}

void Array::deserialize(std::ifstream &in) {
  clear();
  int newSize;
  in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

  for (int i = 0; i < newSize; i++) {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    char *buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    append(std::string(buffer));
    delete[] buffer;
  }
}
