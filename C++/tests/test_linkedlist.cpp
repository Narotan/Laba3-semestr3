#include "../include/LinkedList.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for LinkedList data structure
TEST(LinkedListTest, ComprehensiveLinkedListTest) {
  LinkedList list;

  // Test 1: Initial state
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());

  // Test 2: Push operations
  list.pushFront("third");
  list.pushFront("second");
  list.pushFront("first");
  EXPECT_EQ(list.getSize(), 3);
  EXPECT_EQ(list.get(0), "first");
  EXPECT_EQ(list.get(2), "third");

  list.pushBack("fourth");
  EXPECT_EQ(list.getSize(), 4);
  EXPECT_EQ(list.get(3), "fourth");

  // Test 3: Insert at index
  list.insert(2, "inserted");
  EXPECT_EQ(list.getSize(), 5);
  EXPECT_EQ(list.get(2), "inserted");

  // Test 4: Set element
  list.set(0, "modified");
  EXPECT_EQ(list.get(0), "modified");

  // Test 5: Pop operations
  list.popFront();
  EXPECT_EQ(list.getSize(), 4);
  EXPECT_EQ(list.get(0), "second");

  list.popBack();
  EXPECT_EQ(list.getSize(), 3);

  // Test 6: Remove by index
  list.remove(1);
  EXPECT_EQ(list.getSize(), 2);

  // Test 7: Remove by value
  list.pushBack("target");
  EXPECT_TRUE(list.removeByValue("target"));
  EXPECT_FALSE(list.removeByValue("nonexistent"));

  // Test 8: Copy constructor
  LinkedList list2(list);
  EXPECT_EQ(list2.getSize(), list.getSize());

  // Test 9: Assignment operator
  LinkedList list3;
  list3 = list;
  EXPECT_EQ(list3.getSize(), list.getSize());

  // Test 10: Serialization
  std::ofstream out("test_linkedlist.bin", std::ios::binary);
  list.serialize(out);
  out.close();

  LinkedList list4;
  std::ifstream in("test_linkedlist.bin", std::ios::binary);
  list4.deserialize(in);
  in.close();

  EXPECT_EQ(list4.getSize(), list.getSize());
  std::remove("test_linkedlist.bin");

  // Test 11: Clear
  list.clear();
  EXPECT_EQ(list.getSize(), 0);
  EXPECT_TRUE(list.empty());
}
