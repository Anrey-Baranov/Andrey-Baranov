//#include <gtest.h>
//#include "../lib_heaps/Heap.h"
//#include "../lib_heaps/MaxHeap.h"
//#include "../lib_heaps/MinHeap.h"
//
//class TestHeap : public ::testing::Test {
//protected:
//    std::vector<int> test_data = { 3, 1, 4, 1, 5, 9, 2, 6 };
//    Heap<int>* heap = nullptr;
//
//    void SetUp() override {
//        heap = new MaxHeap<int>(test_data); // Используем MaxHeap для тестирования базовых функций
//    }
//
//    void TearDown() override {
//        delete heap;
//    }
//};
//
//TEST_F(TestHeap, constructor_with_data) {
//    EXPECT_FALSE(heap->empty());
//    EXPECT_EQ(heap->size(), test_data.size());
//}
//
//TEST_F(TestHeap, insert_and_top) {
//    heap->insert(5);
//    EXPECT_EQ(heap->top(), 9); // 9 уже максимальный в test_data
//    heap->insert(10);
//    EXPECT_EQ(heap->top(), 10);
//}
//
//TEST_F(TestHeap, extract_top) {
//    EXPECT_EQ(heap->extractTop(), 9);
//    EXPECT_EQ(heap->extractTop(), 6);
//    EXPECT_EQ(heap->extractTop(), 5);
//}
//
//TEST_F(TestHeap, empty_heap_operations) {
//    Heap<int>* empty_heap = new MaxHeap<int>();
//    EXPECT_THROW(empty_heap->top(), std::runtime_error);
//    EXPECT_THROW(empty_heap->extractTop(), std::runtime_error);
//    delete empty_heap;
//}