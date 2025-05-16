// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_avltree/AVLTree.h"
#include "../lib_bstree/TBinSearchTree.h" 


class AVLTreeExposer : public AVLTree<int> {
public:
    void printTreeWithRelatives() const {
        std::cout << "\nДерево с родственными связями:\n";
        if (_root) {
            _printTreeWithRelatives(_root, nullptr, nullptr);
        }
        else {
            std::cout << "Дерево пусто\n";
        }
    }

private:
    void _printTreeWithRelatives(AVLTreeNode<int>* node, AVLTreeNode<int>* parent, AVLTreeNode<int>* grandparent) const {
        if (node == nullptr) return;

        // Определяем дядю (если есть дедушка)
        AVLTreeNode<int>* uncle = nullptr;
        if (grandparent != nullptr) {
            uncle = (grandparent->left == parent) ? grandparent->right : grandparent->left;
        }

        // Выводим информацию о текущем узле и его родственниках
        std::cout << "Узел: " << std::setw(2) << node->_value
            << " | Высота: " << node->height
            << " | Баланс: " << balanceFactor(node);

        if (parent) {
            std::cout << " | Родитель: " << parent->_value;
        }
        else {
            std::cout << " | Родитель: ---";
        }

        if (grandparent) {
            std::cout << " | Дедушка: " << grandparent->_value;
        }
        else {
            std::cout << " | Дедушка: ---";
        }

        if (uncle) {
            std::cout << " | Дядя: " << uncle->_value;
        }
        else if (grandparent) {
            std::cout << " | Дядя: ---";
        }
        else {
            std::cout << " | Дядя: ---";
        }

        std::cout << std::endl;

        // Рекурсивно выводим левое и правое поддеревья
        _printTreeWithRelatives(node->left, node, parent);
        _printTreeWithRelatives(node->right, node, parent);
    }

public:
    void testPrivateMethods() {
        std::cout << "\nТестирование приватных методов:\n";

        // Вставка через приватный метод
        AVLTreeNode<int>* g, * p, * u;
        _root = _insert(_root, 25, g, p, u);
        _root = _insert(_root, 15, g, p, u);
        _root = _insert(_root, 35, g, p, u);
        _root = _insert(_root, 10, g, p, u);
        _root = _insert(_root, 20, g, p, u);
        _root = _insert(_root, 30, g, p, u);
        _root = _insert(_root, 40, g, p, u);

        std::cout << "\nДерево после вставки:\n";
        printTreeWithRelatives();

        // Поиск через приватный метод
        AVLTreeNode<int>* found = _search(_root, 20);
        std::cout << "\nПоиск 20: " << (found ? "Найден" : "Не найден") << "\n";

        // Получаем родственников для узла 20
        getRelatives(20, g, p, u);
        std::cout << "Родственники узла 20:\n";
        std::cout << "Родитель: " << (p ? p->_value : -1) << "\n";
        std::cout << "Дедушка: " << (g ? g->_value : -1) << "\n";
        std::cout << "Дядя: " << (u ? u->_value : -1) << "\n";

        // Повороты
        std::cout << "\nТестирование поворотов:\n";
        std::cout << "Корень до поворота: " << _root->_value << "\n";
        _root = rotateRight(_root);
        std::cout << "Корень после правого поворота: " << _root->_value << "\n";
        printTreeWithRelatives();

        _root = rotateLeft(_root);
        std::cout << "\nКорень после левого поворота: " << _root->_value << "\n";
        printTreeWithRelatives();

        // Удаление
        _root = _erase(_root, 15);
        std::cout << "\nПосле удаления 15:\n";
        printTreeWithRelatives();

        // Минимальное значение
        AVLTreeNode<int>* minNode = minValueNode(_root);
        std::cout << "\nМинимальное значение в дереве: " << (minNode ? minNode->_value : -1) << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    AVLTreeExposer tree;

    std::vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90 };
    for (int val : values) {
        tree.insert(val);
    }

    // Выводим дерево с ветвями
    std::cout << "\nСтандартное представление дерева:\n";
    tree.printTree();

    // Выводим дерево с родственными связями
    tree.printTreeWithRelatives();

    // Выводим поуровневый обход с баланс-факторами
    std::cout << "\nПоуровневый обход (значение(баланс)):\n";
    tree.printLevelOrder();

    // Проверяем балансировку
    std::cout << "\nДерево сбалансировано: " << (tree.isBalanced() ? "Да" : "Нет") << std::endl;

    // Тестируем приватные методы
    tree.testPrivateMethods();

    return 0;
}
#endif EASY_EXAMPLE