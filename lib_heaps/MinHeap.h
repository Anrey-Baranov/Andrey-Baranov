#ifndef MINHEAP_H
#define MINHEAP_H

#include "Heap.h"

template <typename T>
class MinHeap : public Heap<T> {
protected:
    bool compare(const T& a, const T& b) const override {
        return a < b;
    }

    void heapify(size_t i) override {
        size_t size = this->data.size();
        if (i >= size) return;

        while (true) {
            size_t smallest = i;
            size_t l = this->left(i);
            size_t r = this->right(i);

            if (l < size && this->data[l] < this->data[smallest]) smallest = l;
            if (r < size && this->data[r] < this->data[smallest]) smallest = r;

            if (smallest == i) break;

            std::swap(this->data[i], this->data[smallest]);
            i = smallest;
        }
    }

public:
    MinHeap() = default;
    explicit MinHeap(const std::vector<T>& array) : Heap<T>(array) {
        this->buildHeap();  
    }

    using Heap<T>::top;
    using Heap<T>::extractTop;
    using Heap<T>::empty;
    using Heap<T>::size;

    T min() const { return this->top(); }
    T remove_min() { return this->extractTop(); }

    T max() const = delete;
    T remove_max() = delete;
};

#endif // MINHEAP_H