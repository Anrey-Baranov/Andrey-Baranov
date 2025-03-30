#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Heap.h"

template <typename T>
class MaxHeap : public Heap<T> {
protected:
    bool compare(const T& a, const T& b) const override {
        if (std::isnan(a) || std::isnan(b)) {
            throw std::runtime_error("NaN comparison detected");
        }
        return a > b;
    }

public:
    MaxHeap() = default;
    explicit MaxHeap(const std::vector<T>& array) : Heap<T>(array) {
        this->buildHeap();
    }

    using Heap<T>::top;
    using Heap<T>::extractTop;
    using Heap<T>::empty;
    using Heap<T>::size;
    using Heap<T>::insert;

    T max() const {
        return this->top();
    }

    T remove_max() {
        return this->extractTop();
    }

    T min() const = delete;
    T remove_min() = delete;
};

#endif // MAXHEAP_H