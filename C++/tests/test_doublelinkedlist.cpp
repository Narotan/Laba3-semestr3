#include "../include/DoubleLinkedList.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for DoubleLinkedList data structure
TEST(DoubleLinkedListTest, ComprehensiveDoubleLinkedListTest) {
  DoubleLinkedList list;

  // Test 1: Initial state
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());

  // Test 2: Push operations (both ends)
  list.pushBack("first");
  list.pushBack("second");
  list.pushFront("zero");
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.get(0), "zero");
  EXPECT_EQ(list.get(2), "second");

  // Test 3: Pop operations (both ends)
  list.popFront();
  EXPECT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.get(0), "first");

  list.popBack();
  EXPECT_EQ(list.getSize(), 1);

  // Test 4: Build larger list for bidirectional access test
  list.clear();
  for (int i = 0; i < 100; i++) {
    list.pushBack("item");
  }
  EXPECT_EQ(list.getSize(), 100);

  // Access from both ends (optimized in implementation)
  EXPECT_EQ(list.get(0), "item");
  EXPECT_EQ(list.get(99), "item");
  EXPECT_EQ(list.get(50), "item");

  // Test 5: Insert
  list.clear();
  list.pushBack("a");
  list.pushBack("c");
  list.insert(1, "b");
  EXPECT_EQ(list.get(1), "b");

  // Test 6: Set
  list.set(0, "modified");
  EXPECT_EQ(list.get(0), "modified");

  // Test 7: Remove operations
  list.remove(1);
  EXPECT_EQ(list.getSize(), 2);

  list.pushBack("target");
  EXPECT_TRUE(list.removeByValue("target"));
  EXPECT_FALSE(list.removeByValue("nonexistent"));

  // Test 8: Copy constructor
  DoubleLinkedList list2(list);
  EXPECT_EQ(list2.getSize(), list.getSize());

  // Test 9: Assignment operator
  DoubleLinkedList list3;
  list3 = list;
  EXPECT_EQ(list3.getSize(), list.getSize());

  // Test 10: Serialization
  std::ofstream out("test_doublelist.bin", std::ios::binary);
  list.serialize(out);
  out.close();

  DoubleLinkedList list4;
  std::ifstream in("test_doublelist.bin", std::ios::binary);
  list4.deserialize(in);
  in.close();

  EXPECT_EQ(list4.getSize(), list.getSize());
  std::remove("test_doublelist.bin");

  // Test 11: Clear
  list.clear();
  EXPECT_EQ(list.getSize(), 0);
}
