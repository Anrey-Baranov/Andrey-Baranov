#include "dsu.h"
#include <stdexcept>

DSU::DSU(int size) : _size(size) {
    _parent = new int[size];
    _rank = new int[size];
    for (int i = 0; i < size; i++) {
        make_set(i + 1);  // Индексация с 1
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

void DSU::make_set(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: Element out of bounds.");
    }
    elem--;  // Приводим к нулевой индексации
    _parent[elem] = elem;
    _rank[elem] = 0;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: Element out of bounds.");
    }
    elem--;  // Приводим к нулевой индексации
    if (_parent[elem] != elem) {
        return find(_parent[elem]);  // Рекурсивный вызов
    }
    return elem;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: Element out of bounds.");
    }
    elem--;  // Приводим к нулевой индексации
    if (_parent[elem] != elem) {
        _parent[elem] = find(_parent[elem]);  // Сжатие пути
    }
    return _parent[elem];
}
