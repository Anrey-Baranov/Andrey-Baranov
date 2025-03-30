// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

#include <vector>
#include "../lib_heaps/Heap.h"
#include "../lib_heaps/MaxHeap.h"
#include "../lib_heaps/MinHeap.h"

std::vector<int> findKLargestElements(const std::vector<int>& arr, size_t k) {
    if (k == 0) return {};
    if (k >= arr.size()) return arr;

    MaxHeap<int> maxHeap(arr);
    std::vector<int> result;

    for (size_t i = 0; i < k; ++i) {
        result.push_back(maxHeap.remove_max());
    }

    return result;
}

int main() {
    std::vector<int> numbers = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    size_t k = 4;

    std::cout << "Original array: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    auto kLargest = findKLargestElements(numbers, k);

    std::cout << k << " largest elements: ";
    for (int num : kLargest) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
/*std::vector<int> findKLargestElementsOptimized(const std::vector<int>& arr, size_t k) {
    if (k == 0) return {};
    if (k >= arr.size()) return arr;

    MinHeap<int> minHeap;

    for (size_t i = 0; i < k; ++i) {
        minHeap.insert(arr[i]);
    }

    for (size_t i = k; i < arr.size(); ++i) {
        if (arr[i] > minHeap.min()) {
            minHeap.remove_min();
            minHeap.insert(arr[i]);
        }
    }

    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.remove_min());
    }

    // Так как MinHeap возвращает элементы в порядке возрастания,
    // а нам нужны в порядке убывания, разворачиваем результат
    std::reverse(result.begin(), result.end());

    return result;
}
*/
#endif  // EASY_EXAMPLE
