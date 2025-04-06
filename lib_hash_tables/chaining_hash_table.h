#include <list>
#include <vector>
#include <string>
#include <stdexcept>

template <typename TKey, typename TValue>
class ChainingHashTable {
private:
    struct KeyValuePair {
        TKey key;
        TValue value;

        KeyValuePair(const TKey& k, const TValue& v) : key(k), value(v) {}
    };

    std::vector<std::list<KeyValuePair>> table;
    size_t count;
    size_t capacity;

    size_t hash(const TKey& key) const {
        std::hash<TKey> hasher;
        return hasher(key) % capacity;
    }

    void rehash() {
        std::vector<std::list<KeyValuePair>> oldTable = table;
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        count = 0;

        for (auto& chain : oldTable) {
            for (auto& pair : chain) {
                insert(pair.key, pair.value);
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
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                throw std::runtime_error("Duplicate key");
            }
        }

        table[index].emplace_back(key, value);
        count++;
    }

    bool find(const TKey& key, TValue& value) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                value = pair.value;
                return true;
            }
        }
        return false;
    }

    bool remove(const TKey& key) {
        size_t index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
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

    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            if (!table[i].empty()) {
                std::cout << i << ": ";
                for (const auto& pair : table[i]) {
                    std::cout << pair.key << " -> " << pair.value << "; ";
                }
                std::cout << std::endl;
            }
        }
    }
};