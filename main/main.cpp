// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include <vector>
#include "Heap.h"
#include "MaxHeap.h"

std::vector<int> findKLargestElements(const std::vector<int>& arr, size_t k) {
    if (k == 0) return {};
    if (k >= arr.size()) return arr;

    try {
        MaxHeap<int> maxHeap(arr);
        std::vector<int> result;
        result.reserve(k);

        for (size_t i = 0; i < k && !maxHeap.empty(); ++i) {
            result.push_back(maxHeap.remove_max());
        }

        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in findKLargestElements: " << e.what() << std::endl;
        return {};
    }
}

int main() {
    try {
        std::vector<int> numbers = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
        size_t k = 4;

        std::cout << "Original array: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << "\n";

        auto kLargest = findKLargestElements(numbers, k);

        std::cout << k << " largest elements: ";
        for (int num : kLargest) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
#endif // EASY_EXAMPLE