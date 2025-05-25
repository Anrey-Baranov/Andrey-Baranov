#ifndef TRBTREE_H
#define TRBTREE_H

#include <iostream>
#include <Windows.h>
#include <queue>
#include <stdexcept>
#include <string>


enum Color { RED, BLACK, DOUBLE_BLACK };

template <class T>
class RBTreeNode {
public:
    T _value;
    Color color;
    RBTreeNode<T>* left;
    RBTreeNode<T>* right;
    RBTreeNode<T>* parent;

    RBTreeNode(T value, Color c = RED, RBTreeNode<T>* p = nullptr)
        : _value(value), color(c), left(nullptr), right(nullptr), parent(p) {
    }

};

template <class T>
class RBTree {
    friend class RBTreePrivateTest;
    friend class RBTreeTest;
    friend int main();

public:
    RBTree() : _root(nullptr) {
        setupConsole();
    }
    void setRoot(RBTreeNode<T>* root) { _root = root; }
    ~RBTree() { clear(); }
    
    void insert(T val) {//?
        if (search(val) != nullptr) {
            /*return;*/  // Дубликат - игнорируем
            throw std::runtime_error("Duplicate value insertion attempted");
        }
        RBTreeNode<T>* node = new RBTreeNode<T>(val);
        _root = insertHelper(_root, node);
        if (_root->parent != nullptr) {  // Дополнительная проверка
            _root->parent = nullptr;
        }
        fixInsert(node);
    }

    void erase(T val) {
        RBTreeNode<T>* z = search(val);
        if (z == nullptr) return;

        RBTreeNode<T>* y = z;
        RBTreeNode<T>* x = nullptr;
        RBTreeNode<T>* y_parent = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minValueNode(z->right);
            y_original_color = y->color;
            x = y->right;
            y_parent = y->parent; // Сохраняем родителя y

            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK) {
            if (x != nullptr) {
                fixDelete(x);
            }
            else if (y != nullptr) { // Добавляем проверку на y
                // Создаем фиктивный узел
                RBTreeNode<T>* phantom = new RBTreeNode<T>(0, BLACK);
                phantom->parent = y;

                // Если y был перемещен, используем сохраненного родителя
                if (y_parent && y_parent != z) {
                    phantom->parent = y_parent;
                }

                // Помещаем фиктивный узел в соответствующее поддерево
                if (y->left == nullptr) {
                    y->left = phantom;
                }
                else {
                    y->right = phantom;
                }

                fixDelete(phantom);

                // Удаляем фиктивный узел
                if (phantom->parent->left == phantom) {
                    phantom->parent->left = nullptr;
                }
                else {
                    phantom->parent->right = nullptr;
                }
                delete phantom;
            }
        }

        // Гарантируем, что корень всегда черный
        if (_root != nullptr) {
            _root->color = BLACK;
        }
    }

    void clear() {
        clearHelper(_root);
        _root = nullptr;
    }

    RBTreeNode<T>* getMin() const {
        return minValueNode(_root);
    }

    RBTreeNode<T>* getMax() const {
        return maxValueNode(_root);
    }

    void levelOrder() const {
        if (_root == nullptr) { 
            /*std::cout << "Empty tree" << std::endl;*/
            return; 
        }

        std::queue<RBTreeNode<T>*> q;
        q.push(_root);

        while (!q.empty()) {
            RBTreeNode<T>* node = q.front();
            q.pop();

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (node->color == RED) {
                SetConsoleTextAttribute(hConsole, 12); // Красный
                std::cout << "[" << node->_value << "] ";
            }
            else {
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << "(" << node->_value << ") ";
            }
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        std::cout << std::endl;
    }

    RBTreeNode<T>* search(T val) const {
        return searchHelper(_root, val);
    }

    void print() const {
        if (_root == nullptr) {
            /*std::cout << "Empty tree" << std::endl;*/
        }
        else {
            printHelper(_root, "", true);
        }
    }
    RBTreeNode<T>* getRoot() const { return _root; }

private:
    RBTreeNode<T>* _root;
    // Настройки консоли
    void setupConsole() {
        // Устанавливаем кодировку для русских букв
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
    }
   
    void rotateLeft(RBTreeNode<T>* x) {
        if (x == nullptr || x->right == nullptr) return;

        RBTreeNode<T>* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            _root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        // Сохраняем цвет исходного узла x и устанавливаем его в красный
        y->color = x->color;
        x->color = RED;
    }

    void rotateRight(RBTreeNode<T>* x) {
        /*
        Правый поворот вокруг узла x:
              x               y
             / \             / \
            y   c    =>     a   x
           / \                 / \
          a   b               b   c
        */
        if (x == nullptr || x->left == nullptr) return;

        RBTreeNode<T>* y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            _root = y;
            y->parent = nullptr;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;

        // Всегда сохраняем цвет исходного корня
        y->color = x->color;
        x->color = RED;  // Старый корень становится красным
    }


    void fixInsert(RBTreeNode<T>* k) {
        if (k == nullptr) return;

        // Случай 1: k - корень (просто красим в чёрный)
        if (k == _root) {
            k->color = BLACK;
            return;
        }

        RBTreeNode<T>* parent = k->parent;
        RBTreeNode<T>* grandparent = (parent != nullptr) ? parent->parent : nullptr;
        RBTreeNode<T>* uncle = nullptr;

        while (parent != nullptr && parent->color == RED) {
            grandparent = parent->parent;
            if (grandparent == nullptr) break;  // parent - корень (невозможно, т.к. корень чёрный)

            if (parent == grandparent->left) {
                uncle = grandparent->right;

                // Случай 1: дядя красный
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    k = grandparent;
                    parent = k->parent;
                }
                else {
                    // Случай 2: дядя чёрный и k - правый ребёнок
                    if (k == parent->right) {
                        k = parent;
                        rotateLeft(k);
                        parent = k->parent;
                        grandparent = (parent != nullptr) ? parent->parent : nullptr;
                    }                    

                    // Случай 3: дядя чёрный и k - левый ребёнок
                    if (parent != nullptr && grandparent != nullptr) {
                        parent->color = BLACK;
                        grandparent->color = RED;
                        rotateRight(grandparent);
                    }
                }
            }
            else {
                // Симметричный случай, если parent - правый ребёнок
                uncle = grandparent->left;

                // Случай 1: дядя красный
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    k = grandparent;
                    parent = k->parent;
                }
                else {
                    // Случай 2: дядя чёрный и k - левый ребёнок
                    if (k == parent->left) {
                        k = parent;
                        rotateRight(k);
                        parent = k->parent;
                        grandparent = (parent != nullptr) ? parent->parent : nullptr;
                    }

                    // Случай 3: дядя чёрный и k - правый ребёнок
                    if (parent != nullptr && grandparent != nullptr) {
                        parent->color = BLACK;
                        grandparent->color = RED;
                        rotateLeft(grandparent);
                    }
                }
            }
        }

        // Корень всегда чёрный
        _root->color = BLACK;
    }


    void fixDelete(RBTreeNode<T>* x) {
        while (x != _root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTreeNode<T>* s = x->parent->right;

                // Добавляем проверку на nullptr
                if (s == nullptr) break;

                // Случай 1: брат красный
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                    // Проверяем после поворота
                    if (s == nullptr) break;
                }

                // Случай 2: оба ребенка брата черные
                if ((s->left == nullptr || s->left->color == BLACK) &&
                    (s->right == nullptr || s->right->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    // Случай 3: правый ребенок брата черный, левый красный
                    if (s->right == nullptr || s->right->color == BLACK) {
                        if (s->left != nullptr) {
                            s->left->color = BLACK;
                        }
                        s->color = RED;
                        rotateRight(s);
                        s = x->parent->right;
                        // Проверяем после поворота
                        if (s == nullptr) break;
                    }

                    // Случай 4: левый ребенок брата черный, правый красный
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->right != nullptr) {
                        s->right->color = BLACK;
                    }
                    rotateLeft(x->parent);
                    x = _root;
                }
            }
            else {
                // Симметричный случай для правого поддерева
                RBTreeNode<T>* s = x->parent->left;

                // Проверка на nullptr
                if (s == nullptr) break;

                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    s = x->parent->left;
                    // Проверяем после поворота
                    if (s == nullptr) break;
                }

                if ((s->right == nullptr || s->right->color == BLACK) &&
                    (s->left == nullptr || s->left->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    if (s->left == nullptr || s->left->color == BLACK) {
                        if (s->right != nullptr) {
                            s->right->color = BLACK;
                        }
                        s->color = RED;
                        rotateLeft(s);
                        s = x->parent->left;
                        // Проверяем после поворота
                        if (s == nullptr) break;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->left != nullptr) {
                        s->left->color = BLACK;
                    }
                    rotateRight(x->parent);
                    x = _root;
                }
            }
        }

        // Гарантируем, что x всегда черный
        if (x != nullptr) {
            x->color = BLACK;
        }
    }

    RBTreeNode<T>* searchHelper(RBTreeNode<T>* node, T val) const {
        if (node == nullptr || node->_value == val) {
            return node;
        }
        if (val < node->_value) {
            return searchHelper(node->left, val);
        }
        return searchHelper(node->right, val);
    }

    RBTreeNode<T>* insertHelper(RBTreeNode<T>* root, RBTreeNode<T>* pt) {//?
        if (root == nullptr) {
            pt->parent = nullptr;
            return pt;
        }

        if (pt->_value < root->_value) {
            root->left = insertHelper(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->_value > root->_value) {
            root->right = insertHelper(root->right, pt);
            root->right->parent = root;
        }
        else {
            // Дубликат: игнорируем вставку и удаляем новый узел
            delete pt;
            return root;
        }
        return root;
    }

    void clearHelper(RBTreeNode<T>* node) {
        if (node == nullptr) return;

        // Сначала сохраняем детей, так как после удаления node доступ к ним будет невалидным
        RBTreeNode<T>* left = node->left;
        RBTreeNode<T>* right = node->right;

        delete node;
        clearHelper(left);
        clearHelper(right);
    }

    RBTreeNode<T>* minValueNode(RBTreeNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    RBTreeNode<T>* maxValueNode(RBTreeNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void transplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
        if (u == nullptr) return;

        if (u->parent == nullptr) {
            _root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }

        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void printHelper(RBTreeNode<T>* root, std::string indent, bool last) const {
        // Добавляем проверку на корректность указателя
        if (root == nullptr || reinterpret_cast<uintptr_t>(root) == 0xFFFFFFFFFFFFFFFB) {
            return;
        }

        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "     ";
        }
        else {
            std::cout << "L----";
            indent += "|    ";
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (root->color == RED) {
            SetConsoleTextAttribute(hConsole, 12); // Красный
            std::cout << "[" << root->_value << "]" << std::endl;
        }
        else {
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "(" << root->_value << ")" << std::endl;
        }
        SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет

        // Рекурсивный вывод с проверками
        if (root->left != nullptr && reinterpret_cast<uintptr_t>(root->left) != 0xFFFFFFFFFFFFFFFB) {
            printHelper(root->left, indent, false);
        }
        if (root->right != nullptr && reinterpret_cast<uintptr_t>(root->right) != 0xFFFFFFFFFFFFFFFB) {
            printHelper(root->right, indent, true);
        }
    }
};

#endif //TRBTREE_H