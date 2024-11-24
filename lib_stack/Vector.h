#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef> // ��� size_t
#include <new>     // ��� placement new
#include <stdexcept> // ��� std::out_of_range

template <typename T>
class Vector {
    T* data_ = nullptr;    // ��������� �� ������
    size_t size_ = 0;      // ������� ������ �������
    size_t capacity_ = 0;  // ������� �������

    void destroy() {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T(); // �������� ���������� ��� ������� ��������
        }
        delete[] reinterpret_cast<char*>(data_); // ����������� ������
    }

public:
    Vector() = default;

    // ����� ��� ��������� �������� �������
    size_t size() const {
        return size_;
    }

    // ����� ��� ������� � ���������
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    T operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // ����� ��� ���������� ��������
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2); // ����������� �������
        }
        new(data_ + size_) T(value); // ������������ ����� �������
        size_++;
    }

    // ����� ��� �������� ���������� ��������
    void pop_back() {
        if (size_ > 0) {
            data_[--size_].~T(); // �������� ����������
        }
    }

    // ����� ��� ������� �������
    void clear() {
        destroy();
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr; // ����������� ������
    }

    // ����� ��� �������������� ������
    void reserve(size_t capacity) {
        if (capacity <= capacity_) return; // ���� ����� ������� ������ ��� ����� �������

        T* newData = reinterpret_cast<T*>(new char[sizeof(T) * capacity]);
        size_t i = 0;
        try {
            for (i = 0; i < size_; i++) {
                new(newData + i) T(data_[i]); // �������� ��������
            }
            destroy(); // ����������� ������ ������
            data_ = newData; // ��������� �� ����� ������
            capacity_ = capacity; // ��������� �������
        }
        catch (...) {
            for (size_t j = 0; j < i; j++) {
                newData[j].~T(); // �������� ���������� ��� ������������� ���������
            }
            delete[] reinterpret_cast<char*>(newData); // ����������� ������ � ������ ������
            throw; // ������������ ���������� ������
        }
    }

    ~Vector() {
        destroy(); // ����������� ������ � �����������
    }
};

#endif 
