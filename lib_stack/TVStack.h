#ifndef STACK_H
#define STACK_H

#include "Vector.h"  // Подключаем класс Vector

template <typename T>
class TVStack {
    Vector<T> data;  // Используем Vector в качестве контейнера

public:
    using value_type = T;  // Определяем value_type

    void push(const T& value) {
        data.push_back(value);  // Добавляем элемент в стек
    }

    T top() const {
        if (data.size() == 0) {
            throw std::out_of_range("Stack is empty");  // Проверка на пустоту стека
        }
        return data[data.size() - 1];  // Возвращаем верхний элемент
    }

    void pop() {
        if (data.size() == 0) {
            throw std::out_of_range("Stack is empty");  // Проверка на пустоту стека
        }
        data.pop_back();  // Удаляем верхний элемент
    }

    bool isEmpty() const {
        return data.size() == 0;  // Проверка на пустоту стека
    }

    size_t size() const {
        return data.size();  // Возвращаем размер стека
    }
};

#endif
