#ifndef LIB_HASH_OPENHASHTABLE_H_
#define LIB_HASH_OPENHASHTABLE_H_

#include <vector>
#include <stdexcept>
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
        if (capacity == 0) throw std::runtime_error("Zero capacity in hash table");
        return std::hash<TKey>{}(key) % capacity;
    }

    size_t next(size_t index) const {
        return (index + 1) % capacity;
    }

    void rehash() {
        size_t newCapacity = capacity * 2;
        std::vector<TCell> newTable(newCapacity);
        
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].status == CellStatus::OCCUPIED) {
                size_t newIndex = std::hash<TKey>{}(table[i].data.first()) % newCapacity;
                
                while (newTable[newIndex].status == CellStatus::OCCUPIED) {
                    newIndex = next(newIndex);
                }
                
                newTable[newIndex].data = table[i].data;
                newTable[newIndex].status = CellStatus::OCCUPIED;
            }
        }
        
        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    TOpenHashTable(size_t initialCapacity = 16) : count(0), capacity(initialCapacity) {
        if (capacity == 0) capacity = 1;
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
        
        do {
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
                count++;
                return;
            }
            
            index = next(index);
        } while (index != startIndex);
        
        if (foundDeleted) {
            table[deletedIndex].data.make_pair(key, value);
            table[deletedIndex].status = CellStatus::OCCUPIED;
            count++;
            return;
        }
        
        throw std::runtime_error("Table is full");
    }

    bool find(const TKey& key, TValue& value) const {
        size_t index = hash(key);
        size_t startIndex = index;
        
        do {
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
        size_t index = hash(key);
        size_t startIndex = index;
        
        do {
            if (table[index].status == CellStatus::OCCUPIED && 
                table[index].data.first() == key) {
                table[index].status = CellStatus::DELETED;
                count--;
                return true;
            }
            
            if (table[index].status == CellStatus::FREE) {
                break;
            }
            
            index = next(index);
        } while (index != startIndex);
        
        return false;
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }
};

#endif // LIB_HASH_OPENHASHTABLE_H_