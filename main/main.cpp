#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_rbtree/TRBTree.h"

int main() {
    setlocale(LC_ALL, "Russian");
    RBTree<int> tree;

    // Вставка элементов
    std::cout << "Вставляем элементы: 10, 20, 30, 15, 25, 5" << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);

    // Вывод дерева
    std::cout << "\nКрасно-черное дерево (структура):" << std::endl;
    tree.print();

    // Поиск элементов
    std::cout << "\nПоиск элементов:" << std::endl;
    int val = 15;
    auto node = tree.search(val);
    if (node) {
        std::cout << "Элемент " << val << " найден в дереве." << std::endl;
    }
    else {
        std::cout << "Элемент " << val << " не найден в дереве." << std::endl;
    }

    val = 100;
    node = tree.search(val);
    if (node) {
        std::cout << "Элемент " << val << " найден в дереве." << std::endl;
    }
    else {
        std::cout << "Элемент " << val << " не найден в дереве." << std::endl;
    }

    // Минимальный и максимальный элементы
    // Исправлено: используем getter для значения
    std::cout << "\nМинимальный элемент: " << tree._min()->_value << std::endl;
    std::cout << "Максимальный элемент: " << tree._max()->_value << std::endl;

    // Удаление элементов
    std::cout << "\nУдаляем элементы: 15, 10" << std::endl;
    tree.erase(15);
    tree.erase(10);

    // Вывод дерева после удаления
    std::cout << "\nКрасно-черное дерево после удаления:" << std::endl;
    tree.print();

    // Очистка дерева
    std::cout << "\nОчищаем дерево" << std::endl;
    tree.clear();

    // Попытка вывода пустого дерева
    std::cout << "\nПопытка вывода пустого дерева:" << std::endl;
    tree.print();

    return 0;
}

#endif