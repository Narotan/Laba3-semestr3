#include "../include/Array.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for Array data structure
TEST(ArrayTest, ComprehensiveArrayTest) {
  // Test 1: Initial state
  Array arr;
  EXPECT_EQ(arr.getSize(), 0);
  EXPECT_TRUE(arr.empty());

  // Test 2: Append elements
  arr.append("first");
  arr.append("second");
  arr.append("third");
  EXPECT_EQ(arr.getSize(), 3);
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.get(0), "first");
  EXPECT_EQ(arr.get(1), "second");
  EXPECT_EQ(arr.get(2), "third");

  // Test 3: Insert element
  arr.insert(1, "inserted");
  EXPECT_EQ(arr.getSize(), 4);
  EXPECT_EQ(arr.get(1), "inserted");
  EXPECT_EQ(arr.get(2), "second");

  // Test 4: Set element
  arr.set(0, "modified");
  EXPECT_EQ(arr.get(0), "modified");

  // Test 5: Remove by index
  arr.remove(1);
  EXPECT_EQ(arr.getSize(), 3);
  EXPECT_EQ(arr.get(1), "second");

  // Test 6: Remove by value
  EXPECT_TRUE(arr.removeByValue("second"));
  EXPECT_EQ(arr.getSize(), 2);
  EXPECT_FALSE(arr.removeByValue("nonexistent"));

  // Test 7: Out of range access (exceptions)
  EXPECT_THROW(arr.get(10), std::out_of_range);
  EXPECT_THROW(arr.set(10, "value"), std::out_of_range);

  // Test 8: Copy constructor
  Array arr2(arr);
  EXPECT_EQ(arr2.getSize(), arr.getSize());
  EXPECT_EQ(arr2.get(0), arr.get(0));

  // Test 9: Assignment operator
  Array arr3;
  arr3 = arr;
  EXPECT_EQ(arr3.getSize(), arr.getSize());

  // Test 10: Serialization and deserialization
  std::ofstream out("test_array.bin", std::ios::binary);
  arr.serialize(out);
  out.close();

  Array arr4;
  std::ifstream in("test_array.bin", std::ios::binary);
  arr4.deserialize(in);
  in.close();

  EXPECT_EQ(arr4.getSize(), arr.getSize());
  EXPECT_EQ(arr4.get(0), arr.get(0));
  std::remove("test_array.bin");

  // Test 11: Clear
  arr.clear();
  EXPECT_EQ(arr.getSize(), 0);
  EXPECT_TRUE(arr.empty());

  // Test 12: Dynamic resize (add many elements)
  for (int i = 0; i < 100; i++) {
    arr.append("item");
  }
  EXPECT_EQ(arr.getSize(), 100);
}
