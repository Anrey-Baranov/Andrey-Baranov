#pragma once
#include "../lib_bstree/TBinSearchTree.h"
#include "../lib_pair/TPair.h" 

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

    // ƒобавл€ем метод дл€ получени€ исходной пары
    const TPair<KeyType, ValueType>& getPair() const { return pair; }
};

template <typename KeyType, typename ValueType>
class TBSTTable {
private:
    BSearchTree<ComparablePair<KeyType, ValueType>> _data;

public:
    void insert(const KeyType& key, const ValueType& value) {
        _data.insert(ComparablePair<KeyType, ValueType>(key, value));
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
        std::queue<BTreeNode<ComparablePair<KeyType, ValueType>>*> q;
        if (auto root = _data.min()) {
            q.push(root);
            while (!q.empty()) {
                auto node = q.front();
                q.pop();
                count++;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return count;
    }

    class iterator {
        BTreeNode<ComparablePair<KeyType, ValueType>>* current;
        std::queue<BTreeNode<ComparablePair<KeyType, ValueType>>*> nodes;

    public:
        iterator(BTreeNode<ComparablePair<KeyType, ValueType>>* root) : current(nullptr) {
            if (root) {
                nodes.push(root);
                operator++();
            }
        }

        std::pair<KeyType, ValueType> operator*() {
            return { current->_value.first(), current->_value.second() };
        }

        iterator& operator++() {
            if (nodes.empty()) {
                current = nullptr;
            }
            else {
                current = nodes.front();
                nodes.pop();
                if (current->left) nodes.push(current->left);
                if (current->right) nodes.push(current->right);
            }
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    iterator begin() { return iterator(_data.min()); }
    iterator end() { return iterator(nullptr); }
};