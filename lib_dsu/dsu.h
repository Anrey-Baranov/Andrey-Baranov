#ifndef DSU_H
#define DSU_H

#include <stdexcept>

class DSU {
private:
    int _size;
    int* _parent;
    int* _rank;

public:
    DSU(int size = 0);
    ~DSU();
    void make_set(int elem);
    int find(int elem);
    void union_sets(int first, int second);
    void clear();
};
void union_sets(int first, int second);

#endif // DSU_H
