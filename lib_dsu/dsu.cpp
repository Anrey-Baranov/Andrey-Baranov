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
        _parent[elem] = find(_parent[elem]);  // Сжатие пути
    }
    return _parent[elem];
}
void DSU::union_sets(int first, int second) {
    int root1 = find(first);
    int root2 = find(second);

    if (root1 != root2) {
        if (_rank[root1] < _rank[root2]) {
            _parent[root1] = root2;
        }
        else if (_rank[root1] > _rank[root2]) {
            _parent[root2] = root1;
        }
        else {
            _parent[root2] = root1;
            _rank[root1]++;
        }
    }
}
