#ifndef TAVLTREE_H
#define TAVLTREE_H

#include <iostream>
#include <stdexcept>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

template<class T>
class AVLTreeNode {
public:
    T _value;
    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;
    int height;

    AVLTreeNode(T value) : _value(value), left(nullptr), right(nullptr), height(1) {}
};

template <class T>
class AVLTree {
private:
    friend class AVLTreePrivateTest;
    friend class AVLTreeExposer;

    AVLTreeNode<T>* _root;

    int height(AVLTreeNode<T>* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLTreeNode<T>* node) const {
        return height(node->right) - height(node->left);
    }

    void updateHeight(AVLTreeNode<T>* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    // Повороты
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* y) {
        AVLTreeNode<T>* x = y->left;
        y->left = x->right;
        x->right = y;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* x) {
        AVLTreeNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;

        updateHeight(x);
        updateHeight(y);

        return y;
    }
    AVLTreeNode<T>* _rotateLR(AVLTreeNode<T>* node) {
        if (node == nullptr) return node;
        node->left = rotateLeft(node->left);  // Сначала левый поворот для left-поддерева
        return rotateRight(node);             // Затем правый поворот для всего узла
    }

    AVLTreeNode<T>* _rotateRL(AVLTreeNode<T>* node) {
        if (node == nullptr) return node;
        node->right = rotateRight(node->right);  // Сначала правый поворот для right-поддерева
        return rotateLeft(node);                 // Затем левый поворот для всего узла
    }

    AVLTreeNode<T>* balance(AVLTreeNode<T>* node) {
        if (node == nullptr) return node;
        updateHeight(node);

        int bf = balanceFactor(node);

        // Left Left (LL) → правый поворот
        if (bf < -1 && balanceFactor(node->left) <= 0) {
            return rotateRight(node);
        }
        // Left Right (LR) → LR-поворот
        if (bf < -1 && balanceFactor(node->left) > 0) {
            return _rotateLR(node);
        }
        // Right Right (RR) → левый поворот
        if (bf > 1 && balanceFactor(node->right) >= 0) {
            return rotateLeft(node);
        }
        // Right Left (RL) → RL-поворот
        if (bf > 1 && balanceFactor(node->right) < 0) {
            return _rotateRL(node);
        }

        return node;
    }

    AVLTreeNode<T>* _search(AVLTreeNode<T>* node, T val) const {
        if (node == nullptr || node->_value == val) {
            return node;
        }
        if (val < node->_value) {
            return _search(node->left, val);
        }
        return _search(node->right, val);
    }

    AVLTreeNode<T>* _insert(AVLTreeNode<T>* node, T val) {
        if (node == nullptr) {
            return new AVLTreeNode<T>(val);
        }
        if (val < node->_value) {
            node->left = _insert(node->left, val);
        }
        else if (val > node->_value) {
            node->right = _insert(node->right, val);
        }
        else {
            return node; // Дубликаты не допускаются
        }

        return balance(node);
    }

    // Удаление
    AVLTreeNode<T>* minValueNode(AVLTreeNode<T>* node) const {
        AVLTreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AVLTreeNode<T>* _erase(AVLTreeNode<T>* node, T val) {
        if (node == nullptr) return node;

        if (val < node->_value) {
            node->left = _erase(node->left, val);
        }
        else if (val > node->_value) {
            node->right = _erase(node->right, val);
        }
        else {
            if (node->left == nullptr) {
                AVLTreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                AVLTreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            AVLTreeNode<T>* temp = minValueNode(node->right);
            node->_value = temp->_value;
            node->right = _erase(node->right, temp->_value);
        }

        return balance(node);
    }

    void _clear(AVLTreeNode<T>*& node) noexcept {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    void _printTree(AVLTreeNode<T>* node, const std::string& prefix = "", bool isLeft = false) const {
        if (node == nullptr) return;

        std::cout << prefix;
        std::cout << (isLeft ? "|-- " : "\\-- ");
        std::cout << node->_value << std::endl;

        // Рекурсивно выводим левое и правое поддеревья
        _printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
        _printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
    }

    void _printInOrder(AVLTreeNode<T>* node) const noexcept {
        if (node != nullptr) {
            _printInOrder(node->left);
            std::cout << node->_value << " ";
            _printInOrder(node->right);
        }
    }

    bool _isBalanced(AVLTreeNode<T>* node) const {
        if (node == nullptr) return true;

        int bf = balanceFactor(node);
        if (bf < -1 || bf > 1) return false;

        return _isBalanced(node->left) && _isBalanced(node->right);
    }

public:
    AVLTree() : _root(nullptr) {}
    ~AVLTree() { clear(); }

    AVLTreeNode<T>* search(T val) const noexcept {
        return _search(_root, val);
    }

    void insert(T val) {
        _root = _insert(_root, val);
    }

    void erase(T val) {
        _root = _erase(_root, val);
    }

    void clear() noexcept {
        _clear(_root);
    }

    void printInOrder() const noexcept {
        _printInOrder(_root);
        std::cout << std::endl;
    }

    void printTree() const {
        std::cout << "\nДерево с ветвями:\n";
        _printTree(_root);
        std::cout << std::endl;
    }

    void printLevelOrder() const noexcept {
        if (_root == nullptr) return;

        std::queue<AVLTreeNode<T>*> q;
        q.push(_root);

        while (!q.empty()) {
            AVLTreeNode<T>* node = q.front();
            q.pop();

            std::cout << node->_value << "(" << balanceFactor(node) << ") ";

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        std::cout << std::endl;
    }

    bool isBalanced() const {
        return _isBalanced(_root);
    }
};

#endif // TAVLTREE_H