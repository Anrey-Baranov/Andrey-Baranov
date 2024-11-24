#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef> // Для size_t
#include <new>     // Для placement new
#include <stdexcept> // Для std::out_of_range

template <typename T>
class Vector {
    T* data_ = nullptr;    // Указатель на массив
    size_t size_ = 0;      // Текущий размер вектора
    size_t capacity_ = 0;  // Ёмкость вектора

    void destroy() {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T(); // Вызываем деструктор для каждого элемента
        }
        delete[] reinterpret_cast<char*>(data_); // Освобождаем память
    }

public:
    Vector() = default;

    // Метод для получения текущего размера
    size_t size() const {
        return size_;
    }

    // Метод для доступа к элементам
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

    // Метод для добавления элемента
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2); // Увеличиваем ёмкость
        }
        new(data_ + size_) T(value); // Конструируем новый элемент
        size_++;
    }

    // Метод для удаления последнего элемента
    void pop_back() {
        if (size_ > 0) {
            data_[--size_].~T(); // Вызываем деструктор
        }
    }

    // Метод для очистки вектора
    void clear() {
        destroy();
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr; // Освобождаем память
    }

    // Метод для резервирования памяти
    void reserve(size_t capacity) {
        if (capacity <= capacity_) return; // Если новая ёмкость меньше или равна текущей

        T* newData = reinterpret_cast<T*>(new char[sizeof(T) * capacity]);
        size_t i = 0;
        try {
            for (i = 0; i < size_; i++) {
                new(newData + i) T(data_[i]); // Копируем элементы
            }
            destroy(); // Освобождаем старую память
            data_ = newData; // Указываем на новый массив
            capacity_ = capacity; // Обновляем ёмкость
        }
        catch (...) {
            for (size_t j = 0; j < i; j++) {
                newData[j].~T(); // Вызываем деструктор для скопированных элементов
            }
            delete[] reinterpret_cast<char*>(newData); // Освобождаем память в случае ошибки
            throw; // Пробрасываем исключение дальше
        }
    }

    ~Vector() {
        destroy(); // Освобождаем память в деструкторе
    }
};

#endif 
