#ifndef STACK_H
#define STACK_H

#include "Vector.h"  // ���������� ����� Vector

template <typename T>
class TVStack {
    Vector<T> data;  // ���������� Vector � �������� ����������

public:
    using value_type = T;  // ���������� value_type

    void push(const T& value) {
        data.push_back(value);  // ��������� ������� � ����
    }

    T top() const {
        if (data.size() == 0) {
            throw std::out_of_range("Stack is empty");  // �������� �� ������� �����
        }
        return data[data.size() - 1];  // ���������� ������� �������
    }

    void pop() {
        if (data.size() == 0) {
            throw std::out_of_range("Stack is empty");  // �������� �� ������� �����
        }
        data.pop_back();  // ������� ������� �������
    }

    bool isEmpty() const {
        return data.size() == 0;  // �������� �� ������� �����
    }

    size_t size() const {
        return data.size();  // ���������� ������ �����
    }
};

#endif
