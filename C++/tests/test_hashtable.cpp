#include "../include/HashTable.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for HashTable data structure
TEST(HashTableTest, ComprehensiveHashTableTest) {
  HashTable ht;

  // Test 1: Initial state
  EXPECT_EQ(ht.getSize(), 0);
  EXPECT_TRUE(ht.empty());

  // Test 2: Insert key-value pairs
  ht.insert("name", "John");
  ht.insert("age", "25");
  ht.insert("city", "Moscow");
  EXPECT_EQ(ht.getSize(), 3);
  EXPECT_FALSE(ht.empty());

  // Test 3: Get values
  EXPECT_EQ(ht.get("name"), "John");
  EXPECT_EQ(ht.get("age"), "25");
  EXPECT_EQ(ht.get("city"), "Moscow");

  // Test 4: Get non-existent key (exception)
  EXPECT_THROW(ht.get("nonexistent"), std::runtime_error);

  // Test 5: Contains
  EXPECT_TRUE(ht.contains("name"));
  EXPECT_FALSE(ht.contains("country"));

  // Test 6: Update value
  ht.insert("name", "Jane");
  EXPECT_EQ(ht.get("name"), "Jane");
  EXPECT_EQ(ht.getSize(), 3); // Size shouldn't change

  // Test 7: Remove
  ht.remove("age");
  EXPECT_EQ(ht.getSize(), 2);
  EXPECT_FALSE(ht.contains("age"));

  // Test 8: Collision handling and rehashing
  // Insert many elements to trigger rehash
  for (int i = 0; i < 100; i++) {
    ht.insert("key" + std::to_string(i), "value" + std::to_string(i));
  }
  EXPECT_EQ(ht.getSize(), 102); // 2 original + 100 new

  // Verify all elements are accessible after rehash
  EXPECT_EQ(ht.get("key50"), "value50");
  EXPECT_EQ(ht.get("name"), "Jane");

  // Test 9: Copy constructor
  HashTable ht2(ht);
  EXPECT_EQ(ht2.getSize(), ht.getSize());
  EXPECT_EQ(ht2.get("name"), "Jane");

  // Test 10: Assignment operator
  HashTable ht3;
  ht3 = ht;
  EXPECT_EQ(ht3.getSize(), ht.getSize());

  // Test 11: Serialization
  HashTable ht4;
  ht4.insert("test1", "val1");
  ht4.insert("test2", "val2");

  std::ofstream out("test_hashtable.bin", std::ios::binary);
  ht4.serialize(out);
  out.close();

  HashTable ht5;
  std::ifstream in("test_hashtable.bin", std::ios::binary);
  ht5.deserialize(in);
  in.close();

  EXPECT_EQ(ht5.getSize(), 2);
  EXPECT_EQ(ht5.get("test1"), "val1");
  std::remove("test_hashtable.bin");

  // Test 12: Clear
  ht4.clear();
  EXPECT_EQ(ht4.getSize(), 0);
  EXPECT_TRUE(ht4.empty());
}
