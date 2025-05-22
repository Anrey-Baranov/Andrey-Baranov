#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "../lib_rbtree/TRBTree.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    RBTree<int> tree;

    std::cout << "Демонстрация работы красно-черного дерева\n";
    std::cout << "=======================================\n";

    // Вставка элементов
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    tree.insert(55);
    tree.insert(65);
    tree.insert(75);
    tree.insert(90);
    tree.insert(66);

    std::cout << "\nДерево после вставки элементов:\n";
    tree.print();
    // Поиск элемента
    auto found = tree.search(40);
    std::cout << "\nПоиск 40: " << (found ? "Найден" : "Не найден") << "\n";

    // Удаление элементов
    std::cout << "\nУдаление элементов 70,60 и 65:\n";
    tree.erase(70);
    std::cout << "\n Удаляем 70:\n";
    tree.print();
    tree.erase(60);
    std::cout << "\n Удаляем 60:\n";
    tree.print();
    tree.erase(65);
    std::cout << "\n Удаляем 65:\n";
    std::cout << "\nПроверка после удаления 65:\n";
    std::cout << "65 " << (tree.search(65) ? "найден (ОШИБКА)" : "не найден (OK)") << "\n";
    std::cout << "66 " << (tree.search(66) ? "найден (OK)" : "не найден (ОШИБКА)") << "\n";
    tree.print();

    tree.erase(10);
    std::cout << "\n Удаляем 10:\n";
    tree.print();

    tree.erase(25);
    std::cout << "\n Удаляем 25:\n";
    tree.print();

    tree.erase(35);
    std::cout << "\n Удаляем 35:\n";
    tree.print();

    tree.erase(45);
    std::cout << "\n Удаляем 45:\n";
    tree.print();

    tree.erase(55);
    std::cout << "\n Удаляем 55:\n";
    tree.print();

    tree.erase(90);
    std::cout << "\n Удаляем 90:\n";
    tree.print();

    // Поуровневый обход
    std::cout << "\nПоуровневый обход дерева:\n";
    tree.levelOrder();
    // Минимальное и максимальное значения (используем переименованные методы)
    auto minNode = tree.getMin();
    auto maxNode = tree.getMax();

    std::cout << "\nМинимальное значение в дереве: " << (minNode ? minNode->_value : -1) << "\n";
    std::cout << "Максимальное значение в дереве: " << (maxNode ? maxNode->_value : -1) << "\n";

    return 0;
}

#endif // EASY_EXAMPLE