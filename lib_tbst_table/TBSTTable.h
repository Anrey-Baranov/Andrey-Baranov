#pragma once
#include "../lib_bstree/TBinSearchTree.h"
#include "../lib_pair/TPair.h" 
#include <stack>

template <typename KeyType, typename ValueType>
class ComparablePair {
    TPair<KeyType, ValueType> pair;
public:
    ComparablePair(const KeyType& key, const ValueType& value) : pair(key, value) {}
    ComparablePair(const TPair<KeyType, ValueType>& p) : pair(p) {}

    bool operator<(const ComparablePair& other) const {
        return pair.first() < other.pair.first();
    }

    bool operator>(const ComparablePair& other) const {
        return pair.first() > other.pair.first();
    }

    bool operator==(const ComparablePair& other) const {
        return pair.first() == other.pair.first();
    }

    const KeyType& first() const { return pair.first(); }
    const ValueType& second() const { return pair.second(); }

    const TPair<KeyType, ValueType>& getPair() const { return pair; }
};

template <typename KeyType, typename ValueType>
class TBSTTable {
private:
    BSearchTree<ComparablePair<KeyType, ValueType>> _data;

public:
    void insert(const KeyType& key, const ValueType& value) {
        ComparablePair<KeyType, ValueType> newPair(key, value);
        auto found = _data.search(newPair);
        if (found) {
            // Если ключ уже существует, обновляем значение
            const_cast<ComparablePair<KeyType, ValueType>&>(found->_value) = newPair;
        }
        else {
            _data.insert(newPair);
        }
    }

    bool find(const KeyType& key, ValueType& value) const {
        ComparablePair<KeyType, ValueType> searchPair(key, ValueType());
        auto found = _data.search(searchPair);
        if (found) {
            value = found->_value.second();
            return true;
        }
        return false;
    }

    bool erase(const KeyType& key) {
        ComparablePair<KeyType, ValueType> erasePair(key, ValueType());
        if (_data.search(erasePair)) {
            _data.erase(erasePair);
            return true;
        }
        return false;
    }

    void clear() {
        _data.clear();
    }

    bool empty() const {
        return _data.min() == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        std::stack<BTreeNode<ComparablePair<KeyType, ValueType>>*> stack;
        auto current = _data.min();

        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();
            count++;

            current = current->right;
        }
        return count;
    }

    class iterator {
        std::stack<BTreeNode<ComparablePair<KeyType, ValueType>>*> stack;
        BTreeNode<ComparablePair<KeyType, ValueType>>* current;

    public:
        iterator(BTreeNode<ComparablePair<KeyType, ValueType>>* root) : current(root) {
            if (current) {
                // Переходим к самому левому узлу
                while (current->left) {
                    stack.push(current);
                    current = current->left;
                }
            }
        }

        std::pair<KeyType, ValueType> operator*() {
            return { current->_value.first(), current->_value.second() };
        }

        iterator& operator++() {
            if (current->right) {
                current = current->right;
                while (current->left) {
                    stack.push(current);
                    current = current->left;
                }
            }
            else if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
            else {
                current = nullptr;
            }
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    iterator begin() {
        auto minNode = _data.min();
        if (minNode) {
            while (minNode->left) {
                minNode = minNode->left;
            }
        }
        return iterator(minNode);
    }

    iterator end() { return iterator(nullptr); }
};