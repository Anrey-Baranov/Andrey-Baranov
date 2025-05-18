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
    
    void insert(T val) {
        if (search(val) != nullptr) {
            return;  // Дубликат - игнорируем
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
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant2(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant2(z, z->left);
        }
        else {
            y = minValueNode(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y != z->right) {
                transplant2(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
            }
            else {
                if (x != nullptr) {
                    x->parent = y;
                }
            }

            transplant2(z, y);
            y->left = z->left;
            if (y->left != nullptr) {
                y->left->parent = y;
            }
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK) {
            if (x != nullptr) {
                // Добавляем проверку на существование родителя
                if (x->parent != nullptr) {
                    fixDelete(x);
                }
            }
            else {
                // Создаем фиктивный узел для случаев, когда x - nullptr
                RBTreeNode<T>* phantom = new RBTreeNode<T>(0, BLACK);
                // Устанавливаем родителя фиктивного узла
                if (y != nullptr) {
                    phantom->parent = y->parent;
                    // Если y стал корнем, обновляем parent фиктивного узла
                    if (y == _root) {
                        phantom->parent = nullptr;
                    }
                }
                else {
                    phantom->parent = z->parent;
                }

                // Если дерево не пустое, выполняем фиксацию
                if (_root != nullptr) {
                    fixDelete(phantom);
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
            std::cout << "Empty tree" << std::endl;
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
                SetConsoleTextAttribute(hConsole, 1); //Синий (чёрный)
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
            std::cout << "Empty tree" << std::endl;
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
    
    //void rotateLeft(RBTreeNode<T>* x) {
    //    /*
    //    Левый поворот вокруг узла x:
    //          x               y
    //         / \             / \
    //        a   y    =>     x   c
    //           / \         / \
    //          b   c       a   b
    //    */
    //    if (x == nullptr || x->right == nullptr) return;

    //    RBTreeNode<T>* y = x->right;
    //    x->right = y->left;

    //    if (y->left != nullptr) {
    //        y->left->parent = x;
    //    }

    //    y->parent = x->parent;

    //    if (x->parent == nullptr) {
    //        _root = y;
    //        y->parent = nullptr;
    //    }
    //    else if (x == x->parent->left) {
    //        x->parent->left = y;
    //    }
    //    else {
    //        x->parent->right = y;
    //    }

    //    y->left = x;
    //    x->parent = y;
    //    if (y->parent == nullptr) {
    //        y->color = BLACK;
    //    }
    //}
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

    //void fixDelete(RBTreeNode<T>* x) {
    //    if (x == nullptr) return;

    //    while (x != _root && (x == nullptr || x->color == BLACK)) {
    //        if (x == x->parent->left) {
    //            RBTreeNode<T>* s = x->parent->right;

    //            // Случай 1: брат красный
    //            if (s != nullptr && s->color == RED) {
    //                s->color = BLACK;
    //                x->parent->color = RED;
    //                rotateLeft(x->parent);
    //                s = x->parent->right;
    //            }

    //            // Случай 2: оба ребенка брата черные
    //            if ((s == nullptr) ||
    //                ((s->left == nullptr || s->left->color == BLACK) &&
    //                    (s->right == nullptr || s->right->color == BLACK))) {
    //                if (s != nullptr) s->color = RED;
    //                x->parent->color = BLACK;
    //                x = x->parent;
    //            }
    //            else {
    //                // Случай 3: правый ребенок брата черный
    //                if (s->right == nullptr || s->right->color == BLACK) {
    //                    if (s->left != nullptr) s->left->color = BLACK;
    //                    s->color = RED;
    //                    rotateRight(s);
    //                    s = x->parent->right;
    //                }

    //                // Случай 4: левый ребенок брата черный
    //                if (s != nullptr) {
    //                    s->color = x->parent->color;
    //                    x->parent->color = BLACK;
    //                    if (s->right != nullptr) s->right->color = BLACK;
    //                    rotateLeft(x->parent);
    //                }
    //                x = _root;
    //            }
    //        }
    //        else {
    //            // Симметричный случай для правого ребенка
    //            RBTreeNode<T>* s = x->parent->left;

    //            if (s != nullptr && s->color == RED) {
    //                s->color = BLACK;
    //                x->parent->color = RED;
    //                rotateRight(x->parent);
    //                s = x->parent->left;
    //            }

    //            if ((s == nullptr) ||
    //                ((s->right == nullptr || s->right->color == BLACK) &&
    //                    (s->left == nullptr || s->left->color == BLACK))) {
    //                if (s != nullptr) s->color = RED;
    //                x = x->parent;
    //            }
    //            else {
    //                if (s->left == nullptr || s->left->color == BLACK) {
    //                    if (s->right != nullptr) s->right->color = BLACK;
    //                    s->color = RED;
    //                    rotateLeft(s);
    //                    s = x->parent->left;
    //                }

    //                if (s != nullptr) {
    //                    s->color = x->parent->color;
    //                    x->parent->color = BLACK;
    //                    if (s->left != nullptr) s->left->color = BLACK;
    //                    rotateRight(x->parent);
    //                }
    //                x = _root;
    //            }
    //        }
    //    }
    //    if (x != nullptr) x->color = BLACK;
    //}

    void fixDelete(RBTreeNode<T>* x) {
        while (x != _root && (x == nullptr || x->color == BLACK)) {
            if (x == x->parent->left) {
                RBTreeNode<T>* s = x->parent->right;

                // Проверка на nullptr брата
                if (s == nullptr) break;

                // Случай 1: брат красный
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                    if (s == nullptr) break;  // Добавляем проверку после поворота
                }

                // Случай 2: оба ребенка брата черные (с проверками на nullptr)
                if ((s->left == nullptr || s->left->color == BLACK) &&
                    (s->right == nullptr || s->right->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    // Случай 3: правый ребенок брата черный
                    if (s->right == nullptr || s->right->color == BLACK) {
                        if (s->left != nullptr) {
                            s->left->color = BLACK;
                        }
                        s->color = RED;
                        rotateRight(s);
                        s = x->parent->right;
                        if (s == nullptr) break;  // Проверка после поворота
                    }

                    // Случай 4: левый ребенок брата черный
                    if (s != nullptr) {
                        s->color = BLACK;
                        x->parent->color = BLACK;
                        if (s->right != nullptr) {
                            s->right->color = BLACK;
                        }
                        rotateLeft(x->parent);
                    }
                    x = _root;
                }
            }
            else {
                // Симметричный случай для правого ребенка
                RBTreeNode<T>* s = x->parent->left;

                if (s == nullptr) break;

                // Случай 1: брат красный
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    s = x->parent->left;
                    if (s == nullptr) break;
                }

                // Случай 2: оба ребенка брата черные
                if ((s->right == nullptr || s->right->color == BLACK) &&
                    (s->left == nullptr || s->left->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    // Случай 3: левый ребенок брата черный
                    if (s->left == nullptr || s->left->color == BLACK) {
                        if (s->right != nullptr) {
                            s->right->color = BLACK;
                        }
                        s->color = RED;
                        rotateLeft(s);
                        s = x->parent->left;
                        if (s == nullptr) break;
                    }

                    // Случай 4: правый ребенок брата черный
                    if (s != nullptr) {
                        s->color = BLACK;
                        x->parent->color = BLACK;
                        if (s->left != nullptr) {
                            s->left->color = BLACK;
                        }
                        rotateRight(x->parent);
                    }
                    x = _root;
                }
            }
        }

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

    RBTreeNode<T>* insertHelper(RBTreeNode<T>* root, RBTreeNode<T>* pt) {
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

        // Явно обнуляем указатели старого узла
        u->parent = nullptr;
        u->left = nullptr;
        u->right = nullptr;
    }
    void transplant2(RBTreeNode<T>* u, RBTreeNode<T>* v) {
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
        if (root != nullptr) {
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
                SetConsoleTextAttribute(hConsole, 1); // Синий (черный)
                std::cout << "(" << root->_value << ")" << std::endl;
            }
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
    
};
#endif //TRBTREE_H