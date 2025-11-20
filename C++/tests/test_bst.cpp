#include "../include/BinarySearchTree.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for BinarySearchTree data structure
TEST(BinarySearchTreeTest, ComprehensiveBSTTest) {
  BinarySearchTree bst;

  // Test 1: Initial state
  EXPECT_EQ(bst.getSize(), 0);
  EXPECT_TRUE(bst.empty());

  // Test 2: Insert elements
  bst.insert("dog");
  bst.insert("cat");
  bst.insert("elephant");
  bst.insert("ant");
  bst.insert("duck");
  EXPECT_EQ(bst.getSize(), 5);
  EXPECT_FALSE(bst.empty());

  // Test 3: Search
  EXPECT_TRUE(bst.search("dog"));
  EXPECT_TRUE(bst.search("cat"));
  EXPECT_TRUE(bst.search("elephant"));
  EXPECT_FALSE(bst.search("bird"));
  EXPECT_FALSE(bst.search("zebra"));

  // Test 4: No duplicates
  bst.insert("dog");           // Try to insert duplicate
  EXPECT_EQ(bst.getSize(), 5); // Size should remain same

  // Test 5: Remove leaf node
  bst.remove("ant");
  EXPECT_EQ(bst.getSize(), 4);
  EXPECT_FALSE(bst.search("ant"));

  // Test 6: Remove node with one child
  bst.insert("bear");
  bst.remove("cat");
  EXPECT_FALSE(bst.search("cat"));
  EXPECT_TRUE(bst.search("bear"));

  // Test 7: Remove node with two children
  bst.remove("dog");
  EXPECT_FALSE(bst.search("dog"));
  EXPECT_TRUE(bst.search("duck"));
  EXPECT_TRUE(bst.search("elephant"));

  // Test 8: Build larger tree
  bst.clear();
  std::string words[] = {"e", "c", "g", "a", "d", "f", "h", "b"};
  for (const auto &word : words) {
    bst.insert(word);
  }
  EXPECT_EQ(bst.getSize(), 8);

  // Verify all are searchable
  for (const auto &word : words) {
    EXPECT_TRUE(bst.search(word));
  }

  // Test 9: Copy constructor
  BinarySearchTree bst2(bst);
  EXPECT_EQ(bst2.getSize(), bst.getSize());
  EXPECT_TRUE(bst2.search("e"));
  EXPECT_TRUE(bst2.search("h"));

  // Test 10: Assignment operator
  BinarySearchTree bst3;
  bst3 = bst;
  EXPECT_EQ(bst3.getSize(), bst.getSize());

  // Test 11: Serialization
  std::ofstream out("test_bst.bin", std::ios::binary);
  bst.serialize(out);
  out.close();

  BinarySearchTree bst4;
  std::ifstream in("test_bst.bin", std::ios::binary);
  bst4.deserialize(in);
  in.close();

  EXPECT_EQ(bst4.getSize(), bst.getSize());
  for (const auto &word : words) {
    EXPECT_TRUE(bst4.search(word));
  }
  std::remove("test_bst.bin");

  // Test 12: Clear
  bst.clear();
  EXPECT_EQ(bst.getSize(), 0);
  EXPECT_TRUE(bst.empty());

  // Test 13: Large dataset
  for (int i = 0; i < 1000; i++) {
    bst.insert("item" + std::to_string(i));
  }
  EXPECT_EQ(bst.getSize(), 1000);
  EXPECT_TRUE(bst.search("item500"));
}
