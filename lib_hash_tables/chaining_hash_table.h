#ifndef CHAINING_HASH_TABLE_H
#define CHAINING_HASH_TABLE_H

#include "../lib_pair/TPair.h"
#include "../lib_list/TList.h"
#include <vector>
#include <stdexcept>

template <typename TKey, typename TValue>
class ChainingHashTable {
private:
    std::vector<TList<TPair<TKey, TValue>>> table;
    size_t count;
    size_t capacity;

    size_t hash(const TKey& key) const {
        std::hash<TKey> hasher;
        return hasher(key) % capacity;
    }

    void rehash() {
        std::vector<TList<TPair<TKey, TValue>>> oldTable = table;
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        count = 0;

        for (auto& chain : oldTable) {
            for (auto it = chain.begin(); it != chain.end(); ++it) {
                TPair<TKey, TValue> pair = *it;
                insert(pair.first(), pair.second());
            }
        }
    }

public:
    ChainingHashTable(size_t initialCapacity = 8) : count(0), capacity(initialCapacity) {
        if (capacity < 1) capacity = 1;
        table.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (count >= capacity * 0.7) {
            rehash();
        }

        size_t index = hash(key);
        TList<TPair<TKey, TValue>>& chain = table[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if ((*it).first() == key) {
                throw std::runtime_error("Duplicate key");
            }
        }

        chain.pushBack(TPair<TKey, TValue>(key, value));
        count++;
    }

    bool find(const TKey& key, TValue& value) const {
        size_t index = hash(key);
        const TList<TPair<TKey, TValue>>& chain = table[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if ((*it).first() == key) {
                value = (*it).second();
                return true;
            }
        }
        return false;
    }

    bool remove(const TKey& key) {
        size_t index = hash(key);
        TList<TPair<TKey, TValue>>& chain = table[index];
        TNode<TPair<TKey, TValue>>* node = chain.begin();

        for (size_t i = 0; i < chain.size(); ++i) {
            if (node->getValue().first() == key) {
                chain.removeBy(i);
                count--;
                return true;
            }
            node = node->getNext();
        }
        return false;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            if (!table[i].isEmpty()) {
                std::cout << i << ": ";
                for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                    std::cout << *it << "; ";
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif // CHAINING_HASH_TABLE_H