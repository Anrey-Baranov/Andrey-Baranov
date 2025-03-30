#ifndef MINHEAP_H
#define MINHEAP_H

#include "Heap.h"

template <typename T>
class MinHeap : public Heap<T> {
protected:
    bool compare(const T& a, const T& b) const override {
        return a < b;
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