#include <iostream>
#include <stdexcept>
#include <queue>

template<class T>
class BTreeNode {
public:
    T _value;
    BTreeNode<T>* left, * right;

    BTreeNode(T value) : _value(value), left(nullptr), right(nullptr) {}
};

template <class T>
class BSearchTree {
    BTreeNode<T>* _head;

    BTreeNode<T>* _search(BTreeNode<T>* node, T val) const {
        if (node == nullptr || node->_value == val) {
            return node;
        }
        if (val < node->_value) {
            return _search(node->left, val);
        }
        return _search(node->right, val);
    }

    BTreeNode<T>* _insert(BTreeNode<T>* node, T val) {
        if (node == nullptr) {
            return new BTreeNode<T>(val);
        }
        if (val < node->_value) {
            node->left = _insert(node->left, val);
        }
        else if (val > node->_value) {
            node->right = _insert(node->right, val);
        }
        return node;
    }

    BTreeNode<T>* minValueNode(BTreeNode<T>* node) {
        BTreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    BTreeNode<T>* maxValueNode(BTreeNode<T>* node) {
        BTreeNode<T>* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    BTreeNode<T>* _erase(BTreeNode<T>* node, T val) {
        if (node == nullptr) return node;

        if (val < node->_value) {
            node->left = _erase(node->left, val);
        }
        else if (val > node->_value) {
            node->right = _erase(node->right, val);
        }
        else {
            if (node->left == nullptr) {
                BTreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BTreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            BTreeNode<T>* temp = minValueNode(node->right);
            node->_value = temp->_value;
            node->right = _erase(node->right, temp->_value);
        }
        return node;
    }

    void _clear(BTreeNode<T>* node) noexcept {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
        }
    }

    void _print(BTreeNode<T>* node) const noexcept {
        if (node != nullptr) {
            _print(node->left);
            std::cout << node->_value << " ";
            _print(node->right);
        }
    }

public:
    BSearchTree() : _head(nullptr) {}
    ~BSearchTree() { clear(); }

    BTreeNode<T>* search(T val) const noexcept {
        return _search(_head, val);
    }

    void insert(T val) {
        _head = _insert(_head, val);
    }

    void erase(T val) {
        _head = _erase(_head, val);
    }

    void clear() noexcept {
        _clear(_head);
        _head = nullptr;
    }

    void print() const noexcept {
        _print(_head);
        std::cout << std::endl;
    }

    BTreeNode<T>* min() {
        return minValueNode(_head);
    }

    BTreeNode<T>* max() {
        return maxValueNode(_head);
    }

    // Обход в ширину (уровневой обход)
    void levelOrder() const noexcept {
        if (_head == nullptr) return;

        std::queue<BTreeNode<T>*> q;
        q.push(_head);

        while (!q.empty()) {
            BTreeNode<T>* node = q.front();
            q.pop();

            std::cout << node->_value << " ";

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        std::cout << std::endl;
    }
};