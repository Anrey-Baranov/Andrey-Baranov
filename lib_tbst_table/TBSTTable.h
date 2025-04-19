#pragma once
#include "../lib_bstree/TBinSearchTree.h"
#include "../lib_pair/TPair.h" 

template <typename KeyType, typename ValueType>
class TBSTTable {
private:
    TPair<KeyType, ValueType> _pair;
    BSearchTree<TPair<KeyType, ValueType>> _data;

public:
    void insert(const KeyType& key, const ValueType& value) {
        _pair.make_pair(key, value);
        _data.insert(_pair);
    }

    bool find(const KeyType& key, ValueType& value) const {
        TPair<KeyType, ValueType> searchPair(key, ValueType());
        auto found = _data.search(searchPair);
        if (found) {
            value = found->_value.second();
            return true;
        }
        return false;
    }

    bool erase(const KeyType& key) {
        TPair<KeyType, ValueType> erasePair(key, ValueType());
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
        std::queue<BTreeNode<TPair<KeyType, ValueType>>*> q;
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
        BTreeNode<TPair<KeyType, ValueType>>* current;
        std::queue<BTreeNode<TPair<KeyType, ValueType>>*> nodes;

    public:
        iterator(BTreeNode<TPair<KeyType, ValueType>>* root) {
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

        bool operator!=(const iterator& other) {
            return current != other.current;
        }
    };

    iterator begin() { return iterator(_data.min()); }
    iterator end() { return iterator(nullptr); }
};