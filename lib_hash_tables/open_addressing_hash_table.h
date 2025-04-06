#ifndef LIB_HASH_OPENHASHTABLE_H_
#define LIB_HASH_OPENHASHTABLE_H_

#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "../lib_pair/TPair.h"

enum class CellStatus {
    FREE,
    OCCUPIED,
    DELETED
};

template <typename TKey, typename TValue>
class TOpenHashTable {
    struct TCell {
        TPair<TKey, TValue> data;
        CellStatus status;

        TCell() : status(CellStatus::FREE) {}
    };

    std::vector<TCell> table;
    size_t count;
    size_t capacity;

    size_t hash(const TKey& key) const {
        if (capacity == 0) throw std::runtime_error("Hash table capacity is zero!");
        return std::hash<TKey>{}(key) % capacity;
    }

    size_t next(size_t index) const {
        return (index + 1) % capacity;
    }

    void rehash() {
        size_t newCapacity = capacity == 0 ? 8 : capacity * 2;
        std::vector<TCell> newTable(newCapacity);

        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].status == CellStatus::OCCUPIED) {
                size_t newIndex = std::hash<TKey>{}(table[i].data.first()) % newCapacity;
                size_t attempts = 0;

                // Находим свободную ячейку в новой таблице
                while (newTable[newIndex].status == CellStatus::OCCUPIED) {
                    if (++attempts > newCapacity) {
                        throw std::runtime_error("Rehash failed - infinite loop");
                    }
                    newIndex = (newIndex + 1) % newCapacity;
                }

                // Переносим данные в новую таблицу
                newTable[newIndex].data.make_pair(table[i].data.first(), table[i].data.second());
                newTable[newIndex].status = CellStatus::OCCUPIED;
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    TOpenHashTable(size_t initialCapacity = 8) : count(0), capacity(std::max<size_t>(8, initialCapacity)) {
        table.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (count * 2 >= capacity) {
            rehash();
        }

        size_t index = hash(key);
        size_t startIndex = index;
        bool foundDeleted = false;
        size_t deletedIndex = 0;
        size_t attempts = 0;

        do {
            if (++attempts > capacity) {
                throw std::runtime_error("Insert failed - infinite loop");
            }

            if (table[index].status == CellStatus::OCCUPIED) {
                if (table[index].data.first() == key) {
                    throw std::runtime_error("Duplicate key");
                }
            }
            else if (table[index].status == CellStatus::DELETED) {
                if (!foundDeleted) {
                    foundDeleted = true;
                    deletedIndex = index;
                }
            }
            else {
                if (foundDeleted) {
                    index = deletedIndex;
                }
                table[index].data.make_pair(key, value);
                table[index].status = CellStatus::OCCUPIED;
                ++count;
                return;
            }

            index = next(index);
        } while (index != startIndex);

        if (foundDeleted) {
            table[deletedIndex].data.make_pair(key, value);
            table[deletedIndex].status = CellStatus::OCCUPIED;
            ++count;
            return;
        }

        throw std::runtime_error("Table is full");
    }

    bool find(const TKey& key, TValue& value) const {
        if (count == 0) return false;

        size_t index = hash(key);
        size_t startIndex = index;
        size_t attempts = 0;

        do {
            if (++attempts > capacity) break;

            if (table[index].status == CellStatus::OCCUPIED &&
                table[index].data.first() == key) {
                value = table[index].data.second();
                return true;
            }

            if (table[index].status == CellStatus::FREE) {
                break;
            }

            index = next(index);
        } while (index != startIndex);

        return false;
    }

    bool remove(const TKey& key) {
        if (count == 0) return false;

        size_t index = hash(key);
        size_t startIndex = index;
        size_t attempts = 0;

        do {
            if (++attempts > capacity) break;

            if (table[index].status == CellStatus::OCCUPIED &&
                table[index].data.first() == key) {
                table[index].status = CellStatus::DELETED;
                --count;
                return true;
            }

            if (table[index].status == CellStatus::FREE) {
                break;
            }

            index = next(index);
        } while (index != startIndex);

        return false;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    size_t get_capacity() const { return capacity; }
};

#endif // LIB_HASH_OPENHASHTABLE_H_