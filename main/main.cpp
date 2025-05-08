// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_avltree/AVLTree.h"
#include "../lib_bstree/TBinSearchTree.h" 
int main() {
    setlocale(LC_ALL, "Russian");

    AVLTree<int> tree;

    // Вставляем элементы
    std::vector<int> values = { 10, 20, 30, 40, 50, 60, 70, 80, 10 };
    for (int val : values) {
        tree.insert(val);
    }

    // Выводим дерево с ветвями
    tree.printTree();

    // Выводим поуровневый обход с баланс-факторами
    std::cout << "\nПоуровневый обход (значение(баланс)):\n";
    tree.printLevelOrder();

    // Проверяем балансировку
    std::cout << "\nДерево сбалансировано: " << (tree.isBalanced() ? "Да" : "Нет") << std::endl;

    tree.printTree();

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