// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_avltree/AVLTree.h"
#include "../lib_bstree/TBinSearchTree.h" 
class AVLTreeExposer : public AVLTree<int> {
public:
    void printPrivateTree() const {
        std::cout << "\nПриватное дерево:\n";
        if (_root) {
            _printTree(_root);  
        }
        else {
            std::cout << "Дерево пусто\n";
        }
    }
    void testPrivateMethods() {
        std::cout << "\nTesting private methods:\n";

        // Вставка через приватный метод
        _root = _insert(_root, 25);
        _root = _insert(_root, 15);
        _root = _insert(_root, 35);

        // Поиск через приватный метод
        AVLTreeNode<int>* found = _search(_root, 15);
        std::cout << "Search for 15: " << (found ? "Found" : "Not found") << "\n";

        std::cout << "Balance factor of root: " << balanceFactor(_root) << "\n";

        std::cout << "Before rotation - root: " << _root->_value << "\n";
        _root = rotateRight(_root);
        std::cout << "After right rotation - root: " << _root->_value << "\n";

        _root = _erase(_root, 15);
        found = _search(_root, 15);
        std::cout << "Search for 15 after deletion: " << (found ? "Found" : "Not found") << "\n";

        printPrivateTree();

        AVLTreeNode<int>* minNode = minValueNode(_root);
        std::cout << "Min value in tree: " << (minNode ? minNode->_value : -1) << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    AVLTreeExposer tree;


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

    tree.testPrivateMethods();

    return 0;
}
#endif
