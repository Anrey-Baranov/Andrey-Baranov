#pragma once
#include "../lib_bstree/TBinSearchTree.h"
#include "../lib_pair/TPair.h" 
#include <queue>
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
    ValueType second() { return pair.second(); }  // Возвращаем по значению
    const ValueType second() const { return pair.second(); }  // Константная версия

    const TPair<KeyType, ValueType>& getPair() const { return pair; }

};

template <typename KeyType, typename ValueType>
class TBSTTable {
private:
    BSearchTree<ComparablePair<KeyType, ValueType>> _data;
    size_t _size = 0;  // Добавляем счетчик элементов

public:
    void insert(const KeyType& key, const ValueType& value) {
        ComparablePair<KeyType, ValueType> newPair(key, value);
        auto found = _data.search(newPair);
        if (found) {
            // Для обновления значения создаем новую пару
            _data.erase(found->_value);
            _data.insert(newPair);
        }
        else {
            _data.insert(newPair);
            _size++;
        }
    }

    bool find(const KeyType& key, ValueType& value) const {
        ComparablePair<KeyType, ValueType> searchPair(key, ValueType());
        auto found = _data.search(searchPair);
        if (found) {
            value = found->_value.second();  // Теперь это работает
            return true;
        }
        return false;
    }


    bool erase(const KeyType& key) {
        ComparablePair<KeyType, ValueType> erasePair(key, ValueType());
        auto found = _data.search(erasePair);
        if (found) {
            _data.erase(erasePair);
            _size--;
            return true;
        }
        return false;
    }

    void clear() {
        _data.clear();
        _size = 0;
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    class iterator {
        std::stack<BTreeNode<ComparablePair<KeyType, ValueType>>*> node_stack;
        BTreeNode<ComparablePair<KeyType, ValueType>>* current;

        void push_left(BTreeNode<ComparablePair<KeyType, ValueType>>* node) {
            while (node != nullptr) {
                node_stack.push(node);
                node = node->left;
            }
        }

    public:
        explicit iterator(BTreeNode<ComparablePair<KeyType, ValueType>>* root) {
            push_left(root);
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            }
            else {
                current = nullptr;
            }
        }

        std::pair<KeyType, ValueType> operator*() const {
            return { current->_value.first(), current->_value.second() };
        }

        iterator& operator++() {
            if (current == nullptr) {
                return *this;
            }

            if (current->right != nullptr) {
                push_left(current->right);
            }

            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
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
        BTreeNode<ComparablePair<KeyType, ValueType>>* node = _data.getRoot();
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return iterator(_data.getRoot());
    }

    iterator end() {
        return iterator(nullptr);
    }
};