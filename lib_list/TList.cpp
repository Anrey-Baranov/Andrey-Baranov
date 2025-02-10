#include "TList.h"
#include <iostream>
// Пример использования:
int main() {
    setlocale(LC_ALL, "Russian");
    TList<int> list;

    // Добавление элементов в список
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);

    // Чтение элементов списка с помощью итератора
    cout << "Элементы списка: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Изменение элементов списка с помощью индексов
    for (int i = 0; i < 4; ++i) {
        int newValue = list.getNode(i)->getValue() + 5; // Увеличиваем значение на 5
        list.replaceNode(list.getNode(i), newValue); // Передаем указатель на узел
    }

    // Чтение измененных элементов списка
    cout << "Измененные элементы списка: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Вставка нового элемента в середину списка
    list.insert(25, 2); // Вставляем 25 на позицию 2

    // Чтение элементов списка после вставки
    cout << "Элементы списка после вставки: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}