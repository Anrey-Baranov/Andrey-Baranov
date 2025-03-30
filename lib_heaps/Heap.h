#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream> 

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
    explicit Heap(const std::vector<T>& array) : data(array) {
        buildHeap();
    }

    virtual ~Heap() = default;

    void buildHeap() {
        if (data.empty()) return;

        for (int i = static_cast<int>(data.size()) / 2 - 1; i >= 0; --i) {
            heapify(static_cast<size_t>(i));
        }
    }

    virtual void heapify(size_t i) {
        size_t size = data.size();
        if (i >= size) return;

        while (true) {
            size_t largest = i;
            size_t l = left(i);
            size_t r = right(i);

            if (l < size && data[l] > data[largest]) largest = l;
            if (r < size && data[r] > data[largest]) largest = r;

            if (largest == i) break;

            std::swap(data[i], data[largest]);
            i = largest;
        }
    }


    virtual void siftUp(size_t i) {
        while (i > 0 && compare(data[i], data[parent(i)])) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    virtual void insert(const T& value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    virtual T extractTop() {
        if (data.empty()) throw std::runtime_error("Heap is empty");

        T root = data[0];
        if (data.size() == 1) {
            data.pop_back();
        }
        else {
            data[0] = data.back();
            data.pop_back();
            heapify(0);
        }
        return root;
    }

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