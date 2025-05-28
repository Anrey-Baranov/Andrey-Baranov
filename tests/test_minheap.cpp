//#include <gtest.h>
//#include "../lib_heaps/MinHeap.h"
//
//class TestMinHeap : public ::testing::Test {
//protected:
//    std::vector<int> test_data = { 3, 1, 4, 1, 5, 9, 2, 6 };
//    MinHeap<int> min_heap;
//
//    void SetUp() override {
//        min_heap = MinHeap<int>(test_data);
//    }
//};
//
//TEST_F(TestMinHeap, min_heap_specific_methods) {
//    EXPECT_EQ(min_heap.min(), min_heap.top());
//    EXPECT_EQ(min_heap.remove_min(), 1);
//    EXPECT_EQ(min_heap.remove_min(), 1);
//}
//
//TEST_F(TestMinHeap, min_heap_property) {
//    int prev = min_heap.extractTop();
//    while (!min_heap.empty()) {
//        int current = min_heap.extractTop();
//        EXPECT_GE(current, prev);
//        prev = current;
//    }
//}
//
//TEST_F(TestMinHeap, min_heap_operations) {
//    MinHeap<int> heap;
//    heap.insert(5);
//    EXPECT_EQ(heap.top(), 5);
//    heap.insert(2);
//    EXPECT_EQ(heap.top(), 2);
//    heap.insert(3);
//    EXPECT_EQ(heap.top(), 2);
//}