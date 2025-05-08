#include <algorithm>
#include <iostream>

template <typename T>
class AVLTree {
private:
    struct AVLNode {
        AVLNode* _left;
        AVLNode* _right;
        AVLNode* _parent;
        int _height;
        T _data;

        AVLNode(const T& data)
            : _left(nullptr), _right(nullptr), _parent(nullptr), _height(1), _data(data) {
        }
    };

    AVLNode* _root;

    int height(AVLNode* node) const {
        return node ? node->_height : 0;
    }

    int balanceFactor(AVLNode* node) const {
        return height(node->_right) - height(node->_left);
    }

    void updateHeight(AVLNode* node) {
        node->_height = std::max(height(node->_left), height(node->_right)) + 1;
    }

    // Повороты
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->_left;
        y->_left = x->_right;
        if (x->_right) x->_right->_parent = y;
        x->_right = y;
        x->_parent = y->_parent;
        y->_parent = x;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->_right;
        x->_right = y->_left;
        if (y->_left) y->_left->_parent = x;
        y->_left = x;
        y->_parent = x->_parent;
        x->_parent = y;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Балансировка узла
    AVLNode* balance(AVLNode* node) {
        updateHeight(node);

        int bf = balanceFactor(node);

        // Left heavy
        if (bf == -2) {
            if (balanceFactor(node->_left) > 0) {
                // LR case
                node->_left = rotateLeft(node->_left);
            }
            // LL case
            return rotateRight(node);
        }
        // Right heavy
        else if (bf == 2) {
            if (balanceFactor(node->_right) < 0) {
                // RL case
                node->_right = rotateRight(node->_right);
            }
            // RR case
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, AVLNode* parent, const T& data) {
        if (!node) {
            AVLNode* newNode = new AVLNode(data);
            newNode->_parent = parent;
            return newNode;
        }

        if (data < node->_data) {
            node->_left = insert(node->_left, node, data);
        }
        else if (node->_data < data) {
            node->_right = insert(node->_right, node, data);
        }
        else {
            // Дубликаты не допускаются
            return node;
        }

        return balance(node);
    }

    // Поиск минимального узла в поддереве
    AVLNode* findMin(AVLNode* node) const {
        while (node && node->_left) {
            node = node->_left;
        }
        return node;
    }

    // Удаление узла
    AVLNode* remove(AVLNode* node, const T& data) {
        if (!node) return nullptr;

        if (data < node->_data) {
            node->_left = remove(node->_left, data);
        }
        else if (node->_data < data) {
            node->_right = remove(node->_right, data);
        }
        else {
            // Найден узел для удаления
            if (!node->_left || !node->_right) {
                AVLNode* temp = node->_left ? node->_left : node->_right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    // Один потомок
                    temp->_parent = node->_parent;
                    *node = *temp; // Копируем данные
                }

                delete temp;
            }
            else {
                // Два потомка
                AVLNode* temp = findMin(node->_right);
                node->_data = temp->_data;
                node->_right = remove(node->_right, temp->_data);
            }
        }

        if (!node) return node;

        return balance(node);
    }

    // Очистка дерева
    void clear(AVLNode* node) {
        if (node) {
            clear(node->_left);
            clear(node->_right);
            delete node;
        }
    }

    // Копирование дерева
    AVLNode* copy(AVLNode* node, AVLNode* parent) {
        if (!node) return nullptr;

        AVLNode* newNode = new AVLNode(node->_data);
        newNode->_parent = parent;
        newNode->_height = node->_height;
        newNode->_left = copy(node->_left, newNode);
        newNode->_right = copy(node->_right, newNode);

        return newNode;
    }

public:
    AVLTree() : _root(nullptr) {}

    AVLTree(const AVLTree& other) {
        _root = copy(other._root, nullptr);
    }

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clear();
            _root = copy(other._root, nullptr);
        }
        return *this;
    }

    ~AVLTree() {
        clear();
    }

    void clear() {
        clear(_root);
        _root = nullptr;
    }

    void insert(const T& data) {
        _root = insert(_root, nullptr, data);
    }

    void remove(const T& data) {
        _root = remove(_root, data);
    }

    bool contains(const T& data) const {
        AVLNode* current = _root;
        while (current) {
            if (data < current->_data) {
                current = current->_left;
            }
            else if (current->_data < data) {
                current = current->_right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    void printInOrder() const {
        printInOrder(_root);
        std::cout << std::endl;
    }

    void printInOrder(AVLNode* node) const {
        if (node) {
            printInOrder(node->_left);
            std::cout << node->_data << " ";
            printInOrder(node->_right);
        }
    }

    // Проверка сбалансированности (для тестирования)
    bool isBalanced() const {
        return isBalanced(_root);
    }

    bool isBalanced(AVLNode* node) const {
        if (!node) return true;

        int bf = balanceFactor(node);
        if (bf < -1 || bf > 1) return false;

        return isBalanced(node->_left) && isBalanced(node->_right);
    }
};