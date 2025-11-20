#include "../include/Stack.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for Stack data structure
TEST(StackTest, ComprehensiveStackTest) {
  Stack stack;

  // Test 1: Initial state
  EXPECT_EQ(stack.getSize(), 0);
  EXPECT_TRUE(stack.empty());

  // Test 2: Push elements
  stack.push("first");
  stack.push("second");
  stack.push("third");
  EXPECT_EQ(stack.getSize(), 3);
  EXPECT_FALSE(stack.empty());

  // Test 3: Peek (without removing)
  EXPECT_EQ(stack.peek(), "third");
  EXPECT_EQ(stack.getSize(), 3);

  // Test 4: LIFO order
  EXPECT_EQ(stack.pop(), "third");
  EXPECT_EQ(stack.pop(), "second");
  EXPECT_EQ(stack.getSize(), 1);

  // Test 5: Pop empty exception
  stack.pop(); // Remove last element
  EXPECT_THROW(stack.pop(), std::runtime_error);
  EXPECT_THROW(stack.peek(), std::runtime_error);

  // Test 6: Copy constructor
  stack.push("bottom");
  stack.push("middle");
  stack.push("top");

  Stack stack2(stack);
  EXPECT_EQ(stack2.getSize(), 3);
  EXPECT_EQ(stack2.pop(), "top");
  EXPECT_EQ(stack2.pop(), "middle");

  // Test 7: Assignment operator
  Stack stack3;
  stack3 = stack;
  EXPECT_EQ(stack3.getSize(), stack.getSize());

  // Test 8: Serialization and deserialization
  std::ofstream out("test_stack.bin", std::ios::binary);
  stack.serialize(out);
  out.close();

  Stack stack4;
  std::ifstream in("test_stack.bin", std::ios::binary);
  stack4.deserialize(in);
  in.close();

  EXPECT_EQ(stack4.getSize(), 3);
  EXPECT_EQ(stack4.pop(), "top");
  EXPECT_EQ(stack4.pop(), "middle");
  EXPECT_EQ(stack4.pop(), "bottom");
  std::remove("test_stack.bin");

  // Test 9: Clear
  stack.clear();
  EXPECT_EQ(stack.getSize(), 0);
  EXPECT_TRUE(stack.empty());
}
