// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_avltree/AVLTree.h"
#include "../lib_bstree/TBinSearchTree.h" 
int main() {
    AVLTree<int> tree;

    // Вставка элементов
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // Вывод дерева
    std::cout << "Inorder traversal: ";
    tree.printInOrder();

    // Проверка сбалансированности
    std::cout << "Tree is balanced: " << (tree.isBalanced() ? "Yes" : "No") << std::endl;

    // Удаление элемента
    tree.remove(30);

    std::cout << "After removal of 30: ";
    tree.printInOrder();

    return 0;
}
//std::vector<int> findKLargestElements(const std::vector<int>& arr, size_t k) {
//    if (k == 0) return {};
//    if (k >= arr.size()) return arr;
//
//    try {
//        MaxHeap<int> maxHeap(arr);
//        std::vector<int> result;
//        result.reserve(k);
//
//        for (size_t i = 0; i < k && !maxHeap.empty(); ++i) {
//            result.push_back(maxHeap.remove_max());
//        }
//
//        return result;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error in findKLargestElements: " << e.what() << std::endl;
//        return {};
//    }
//}
//
//int main() {
//    try {
//        std::vector<int> numbers = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 100, 150000 };
//        size_t k = 4;
//
//        std::cout << "Original array: ";
//        for (int num : numbers) std::cout << num << " ";
//        std::cout << "\n";
//
//        auto kLargest = findKLargestElements(numbers, k);
//
//        std::cout << k << " largest elements: ";
//        for (int num : kLargest) std::cout << num << " ";
//        std::cout << "\n";
//
//        return 0;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//        return 1;
//    }
//}
#endif // EASY_EXAMPLE