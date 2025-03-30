#include <gtest.h>
#include "../lib_heaps/MaxHeap.h"

class TestMaxHeap : public ::testing::Test {
protected:
    std::vector<int> test_data = { 3, 1, 4, 1, 5, 9, 2, 6 };
    MaxHeap<int> max_heap;

    void SetUp() override {
        max_heap = MaxHeap<int>(test_data);
    }
};

TEST_F(TestMaxHeap, max_heap_specific_methods) {
    EXPECT_EQ(max_heap.max(), max_heap.top());
    EXPECT_EQ(max_heap.remove_max(), 9);
    EXPECT_EQ(max_heap.remove_max(), 6);
}

TEST_F(TestMaxHeap, max_heap_property) {
    int prev = max_heap.extractTop();
    while (!max_heap.empty()) {
        int current = max_heap.extractTop();
        EXPECT_LE(current, prev);
        prev = current;
    }
}

TEST_F(TestMaxHeap, build_heap_correctness) {
    std::vector<int> data = { 3, 1, 4, 1, 5, 9, 2, 6 };
    MaxHeap<int> heap(data);
    EXPECT_EQ(heap.top(), 9);
}