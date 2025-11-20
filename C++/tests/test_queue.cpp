#include "../include/Queue.h"
#include <fstream>
#include <gtest/gtest.h>

// Comprehensive test for Queue data structure
TEST(QueueTest, ComprehensiveQueueTest) {
  Queue queue;

  // Test 1: Initial state
  EXPECT_EQ(queue.getSize(), 0);
  EXPECT_TRUE(queue.empty());

  // Test 2: Enqueue elements
  queue.enqueue("first");
  queue.enqueue("second");
  queue.enqueue("third");
  EXPECT_EQ(queue.getSize(), 3);
  EXPECT_FALSE(queue.empty());

  // Test 3: Peek (without removing)
  EXPECT_EQ(queue.peek(), "first");
  EXPECT_EQ(queue.getSize(), 3);

  // Test 4: FIFO order
  EXPECT_EQ(queue.dequeue(), "first");
  EXPECT_EQ(queue.dequeue(), "second");
  EXPECT_EQ(queue.getSize(), 1);

  // Test 5: Dequeue empty exception
  queue.dequeue(); // Remove last element
  EXPECT_THROW(queue.dequeue(), std::runtime_error);
  EXPECT_THROW(queue.peek(), std::runtime_error);

  // Test 6: Interleaved operations
  queue.enqueue("1");
  queue.enqueue("2");
  EXPECT_EQ(queue.dequeue(), "1");
  queue.enqueue("3");
  EXPECT_EQ(queue.peek(), "2");

  // Test 7: Copy constructor
  Queue queue2(queue);
  EXPECT_EQ(queue2.getSize(), queue.getSize());
  EXPECT_EQ(queue2.dequeue(), "2");

  // Test 8: Assignment operator
  queue.enqueue("a");
  queue.enqueue("b");
  Queue queue3;
  queue3 = queue;
  EXPECT_EQ(queue3.getSize(), queue.getSize());

  // Test 9: Serialization and deserialization
  std::ofstream out("test_queue.bin", std::ios::binary);
  queue.serialize(out);
  out.close();

  Queue queue4;
  std::ifstream in("test_queue.bin", std::ios::binary);
  queue4.deserialize(in);
  in.close();

  EXPECT_EQ(queue4.getSize(), queue.getSize());
  // Queue contains: "2", "3", "a", "b" at this point
  EXPECT_EQ(queue4.dequeue(), "2");
  EXPECT_EQ(queue4.dequeue(), "3");
  EXPECT_EQ(queue4.dequeue(), "a");
  EXPECT_EQ(queue4.dequeue(), "b");
  std::remove("test_queue.bin");

  // Test 10: Clear
  queue.clear();
  EXPECT_EQ(queue.getSize(), 0);
  EXPECT_TRUE(queue.empty());
}
