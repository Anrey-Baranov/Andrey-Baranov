#include <iostream>
#include <stdexcept>
#include "../lib_list/TList.h"

template <class T>
class TLStack {
public:
    TList<T> _data;

public:
    using value_type = T;
    inline bool isEmpty() const noexcept {
        return _data.isEmpty();
    }

    void push(const T& val) {
        _data.pushFront(val);
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("TStack is empty");
        }
        _data.removeFirst();
    }

    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("TStack is empty");
        }
        return _data.getNode(0)->getValue(); // Возвращаем значение верхнего элемента
    }

    // Метод для очистки стека
    void clear() {
        _data.clear();
    }
};