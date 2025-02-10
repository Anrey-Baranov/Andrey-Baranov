#include "dsu.h"
#include <stdexcept>

DSU::DSU(int size) : _size(size) {
    _parent = new int[size];
    _rank = new int[size];
    for (int i = 0; i < size; i++) {
        make_set(i + 1);  // ���������� � 1
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
    elem--;  // �������� � ������� ����������
    _parent[elem] = elem;
    _rank[elem] = 0;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: Element out of bounds.");
    }
    elem--;  // �������� � ������� ����������
    if (_parent[elem] != elem) {
        return find(_parent[elem]);  // ����������� �����
    }
    return elem;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Input Error: Element out of bounds.");
    }
    elem--;  // �������� � ������� ����������
    if (_parent[elem] != elem) {
        _parent[elem] = find(_parent[elem]);  // ������ ����
    }
    return _parent[elem];
}
