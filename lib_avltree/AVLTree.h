#ifndef TAVLTREE_H
#define TAVLTREE_H

#include <iostream>
#include <stdexcept>
#include <queue>
#include <vector>
#include <algorithm>

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
    AVLTreeNode<T>* _root;

    // Вспомогательные функции
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

    // Балансировка
    AVLTreeNode<T>* balance(AVLTreeNode<T>* node) {
        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf == -2) {
            if (balanceFactor(node->left) > 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (bf == 2) {
            if (balanceFactor(node->right) < 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    // Поиск
    AVLTreeNode<T>* _search(AVLTreeNode<T>* node, T val) const {
        if (node == nullptr || node->_value == val) {
            return node;
        }
        if (val < node->_value) {
            return _search(node->left, val);
        }
        return _search(node->right, val);
    }

    // Вставка
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

    // Очистка
    void _clear(AVLTreeNode<T>*& node) noexcept {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    // Визуализация с ветвями
    void _printTree(AVLTreeNode<T>* root, int space = 0, int gap = 4) const {
        if (root == nullptr) return;

        space += gap;

        _printTree(root->right, space);

        std::cout << std::endl;
        for (int i = gap; i < space; i++) {
            std::cout << " ";
        }

        // Определяем, есть ли левый или правый потомок
        bool hasLeft = (root->left != nullptr);
        bool hasRight = (root->right != nullptr);

        // Выводим значение узла
        std::cout << root->_value;

        // Выводим ветви на следующей строке
        std::cout << std::endl;
        for (int i = gap; i < space; i++) {
            std::cout << " ";
        }

        if (hasLeft && hasRight) {
            std::cout << "/ \\";
        }
        else if (hasLeft) {
            std::cout << "/";
        }
        else if (hasRight) {
            std::cout << " \\";
        }

        _printTree(root->left, space);
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

private:
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
};

#endif // TAVLTREE_H