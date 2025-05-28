/*
#include <gtest.h>
#include "../lib_queue/queue.h"

class TestQueueLib : public ::testing::Test {
protected:
	TQueue<int> queue_par = TQueue<int>(5);
};

TEST(TestQueue, constructor_def) {
	TQueue<int> queue_def = TQueue<int>();
	EXPECT_EQ(queue_def._capacity, 10);
}

TEST_F(TestQueueLib, constructor_par) {
	EXPECT_EQ(queue_par._capacity, 5);
}

TEST_F(TestQueueLib, check_func_empty) {
	ASSERT_ANY_THROW(queue_par.pop());
}

TEST_F(TestQueueLib, check_func_full) {
	queue_par.push(1);
	queue_par.push(2);
	queue_par.push(3);
	queue_par.push(4);
	queue_par.push(5);
	ASSERT_ANY_THROW(queue_par.push(6));
}

TEST_F(TestQueueLib, check_func_push) {
	queue_par.push(1);
	queue_par.push(2);
	queue_par.push(5);
	ASSERT_EQ(queue_par.top(), 5);
}

TEST_F(TestQueueLib, check_func_pop) {
	queue_par.push(1);
	queue_par.push(2);
	queue_par.push(5);
	queue_par.push(6);
	queue_par.pop();
	queue_par.pop();
	ASSERT_EQ(queue_par.current(), 5);
}

TEST_F(TestQueueLib, check_true_work) {
	queue_par.push(1);
	queue_par.push(2);
	queue_par.push(3);
	queue_par.push(4);
	queue_par.push(5);
	queue_par.pop();
	queue_par.pop();
	queue_par.push(6);
	queue_par.push(7);
	queue_par.pop();
	queue_par.pop();
	queue_par.pop();
	queue_par.pop();
	ASSERT_EQ(queue_par.current(), 7);
}
*/