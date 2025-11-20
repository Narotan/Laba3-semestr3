#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <fstream>

class Array {
private:
    std::string* data;
    int size;
    int capacity;
    
    void resize();
    
public:
    // Constructors and destructor
    Array();
    Array(int initialCapacity);
    Array(const Array& other);
    ~Array();
    
    // Assignment operator
    Array& operator=(const Array& other);
    
    // Basic operations
    void append(const std::string& value);
    void insert(int index, const std::string& value);
    std::string get(int index) const;
    void set(int index, const std::string& value);
    void remove(int index);
    bool removeByValue(const std::string& value);
    
    // Utility methods
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }
    void clear();
    
    // Serialization
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};

#endif // ARRAY_H
