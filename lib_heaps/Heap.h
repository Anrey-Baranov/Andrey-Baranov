#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Heap {
protected:
    std::vector<T> data;

    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }

    virtual bool compare(const T& a, const T& b) const = 0;

public:
    Heap() = default;
    Heap(const std::vector<T>& array) : data(array) {
        buildHeap();
    }

    virtual ~Heap() = default;

    // Построение кучи из неупорядоченного массива
    void buildHeap() {
        for (int i = data.size() / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }

    // Просеивание элемента вниз
    virtual void heapify(size_t i) {
        size_t l = left(i);
        size_t r = right(i);
        size_t target = i;

        if (l < data.size() && compare(data[l], data[target]))
            target = l;
        if (r < data.size() && compare(data[r], data[target]))
            target = r;

        if (target != i) {
            std::swap(data[i], data[target]);
            heapify(target);
        }
    }

    // Просеивание элемента вверх
    virtual void siftUp(size_t i) {
        while (i > 0 && compare(data[i], data[parent(i)])) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    // Добавление элемента в кучу
    virtual void insert(const T& value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    // Извлечение корня кучи
    virtual T extractTop() {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }

        T root = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            heapify(0);
        }
        return root;
    }

    // Получение корня кучи без извлечения
    virtual T top() const {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return data[0];
    }

    virtual bool empty() const {
        return data.empty();
    }

    virtual size_t size() const {
        return data.size();
    }
};

#endif // HEAP_H