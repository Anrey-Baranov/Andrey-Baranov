#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename TKey, typename TValue>
class OpenAddressingHashTable {
private:
    enum class CellStatus {
        FREE,
        OCCUPIED,
        DELETED
    };

    struct HashCell {
        TKey key;
        TValue value;
        CellStatus status;

        HashCell() : status(CellStatus::FREE) {}
    };

    std::vector<HashCell> table;
    size_t count;
    size_t capacity;

    size_t hash1(const TKey& key) const {
        std::hash<TKey> hasher;
        return hasher(key) % capacity;
    }

    // Вторичная хэш-функция (должна возвращать значение, взаимно простое с capacity)
    size_t hash2(const TKey& key) const {
        std::hash<TKey> hasher;
        return 1 + (hasher(key) % (capacity - 1));
    }

    // Поиск следующего свободного слота
    size_t findSlot(const TKey& key, bool forInsert = false) const {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t i = 0;
        size_t firstDeleted = capacity; // Индекс первого удаленного элемента

        while (i < capacity) {
            size_t index = (h1 + i * h2) % capacity;
            const HashCell& cell = table[index];

            if (cell.status == CellStatus::FREE) {
                return forInsert ? (firstDeleted != capacity ? firstDeleted : index) : capacity;
            }
            if (cell.status == CellStatus::DELETED) {
                if (firstDeleted == capacity) {
                    firstDeleted = index;
                }
            }
            else if (cell.key == key) {
                return index;
            }
            i++;
        }

        return forInsert ? firstDeleted : capacity;
    }

    void rehash() {
        std::vector<HashCell> oldTable = table;
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        count = 0;

        for (const auto& cell : oldTable) {
            if (cell.status == CellStatus::OCCUPIED) {
                insert(cell.key, cell.value);
            }
        }
    }

public:
    OpenAddressingHashTable(size_t initialCapacity = 8) : count(0), capacity(initialCapacity) {
        if (capacity < 1) capacity = 1;
        table.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (count >= capacity * 0.7) {
            rehash();
        }

        size_t index = findSlot(key, true);
        if (index == capacity) {
            throw std::runtime_error("Hash table is full");
        }

        if (table[index].status == CellStatus::OCCUPIED && table[index].key == key) {
            throw std::runtime_error("Duplicate key");
        }

        table[index].key = key;
        table[index].value = value;
        table[index].status = CellStatus::OCCUPIED;
        count++;
    }

    bool find(const TKey& key, TValue& value) const {
        size_t index = findSlot(key);
        if (index == capacity) {
            return false;
        }
        value = table[index].value;
        return true;
    }

    bool remove(const TKey& key) {
        size_t index = findSlot(key);
        if (index == capacity) {
            return false;
        }
        table[index].status = CellStatus::DELETED;
        count--;
        return true;
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].status == CellStatus::OCCUPIED) {
                std::cout << i << ": " << table[i].key << " -> " << table[i].value << std::endl;
            }
        }
    }
};