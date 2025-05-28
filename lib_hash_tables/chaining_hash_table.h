#ifndef LIB_HASH_CHAINHASHTABLE_H_
#define LIB_HASH_CHAINHASHTABLE_H_

#include <vector>
#include <stdexcept>
#include "../lib_list/TList.h"
#include "../lib_pair/TPair.h"

template <typename TKey, typename TValue>
class TChainHashTable {
    std::vector<TList<TPair<TKey, TValue>>> table;
    size_t count;
    size_t capacity;

    size_t hash(const TKey& key) const {
        return std::hash<TKey>{}(key) % capacity;
    }

    void rehash() {
        size_t newCapacity = capacity * 2;
        std::vector<TList<TPair<TKey, TValue>>> newTable(newCapacity);

        for (auto& chain : table) {
            for (auto it = chain.begin(); it != chain.end(); ++it) {
                TPair<TKey, TValue> pair = *it;
                size_t newIndex = hash(pair.first()) % newCapacity;
                newTable[newIndex].pushBack(pair);
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    TChainHashTable(size_t initialCapacity = 16) : count(0), capacity(initialCapacity) {
        if (capacity == 0) capacity = 1;
        table.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (count >= capacity * 2) {
            rehash();
        }

        size_t index = hash(key);
        auto& chain = table[index];

        // Проверка на дубликаты
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
        const auto& chain = table[index];

        // Создаем временную копию списка для итерации
        TList<TPair<TKey, TValue>> tempList = chain;
        for (auto it = tempList.begin(); it != tempList.end(); ++it) {
            if ((*it).first() == key) {
                value = (*it).second();
                return true;
            }
        }

        return false;
    }

    bool remove(const TKey& key) {
        size_t index = hash(key);
        auto& chain = table[index];
        size_t pos = 0;

        for (auto it = chain.begin(); it != chain.end(); ++it, ++pos) {
            if ((*it).first() == key) {
                chain.removeBy(pos);
                count--;
                return true;
            }
        }

        return false;
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }
};

#endif // LIB_HASH_CHAINHASHTABLE_H_