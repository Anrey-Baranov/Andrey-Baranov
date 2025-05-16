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
private:
    RBTreeNode<T>* _root;
    // Настройки консоли
    void setupConsole() {
        // Устанавливаем кодировку для русских букв
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        // Настраиваем размер буфера и окна консоли
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = { 100, 500 };
        SMALL_RECT rect = { 0, 0, size.X - 1, size.Y - 1 };
        SetConsoleScreenBufferSize(console, size);
        SetConsoleWindowInfo(console, TRUE, &rect);

        // Устанавливаем белый фон и черный текст
        SetConsoleTextAttribute(console, BACKGROUND_INTENSITY | BACKGROUND_RED |
            BACKGROUND_GREEN | BACKGROUND_BLUE);
        system("cls");
    }
    // Вспомогательные функции
    void rotateLeft(RBTreeNode<T>* x) {
        /*
       Левый поворот вокруг узла x:
             x               y
            / \             / \
           a   y    =>     x   c
              / \         / \
             b   c       a   b
       */
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
        RBTreeNode<T>* y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            _root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    void fixInsert(RBTreeNode<T>* k) {
        /*
        Балансировка после вставки:
        X - текущий узел (красный)
        P - родитель (красный)
        G - дед (черный)
        U - дядя
        */
        RBTreeNode<T>* u;
        while (k->parent != nullptr && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // дядя
                if (u != nullptr && u->color == RED) {
                    // Случай 1: дядя красный - перекрашиваем
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    // Случай 2: дядя черный и узел - левый ребенок
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    // Случай 3: дядя черный и узел - правый ребенок
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right; // дядя
                if (u != nullptr && u->color == RED) {
                    // Случай 1: дядя красный
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    // Случай 2: дядя черный и узел - правый ребенок
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Случай 3: дядя черный и узел - левый ребенок
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            }
            if (k == _root) break;
        }
        _root->color = BLACK;
    }

    void fixDelete(RBTreeNode<T>* x) {
        /*
        Балансировка после удаления:
        X - текущий узел (двойной черный)
        P - родитель
        S - брат
        */
        if (x == nullptr) return;

        while (x != _root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTreeNode<T>* s = x->parent->right;
                // Случай 1: брат красный
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }
                // Случай 2: оба ребенка брата черные
                if ((s->left == nullptr || s->left->color == BLACK) &&
                    (s->right == nullptr || s->right->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    // Случай 3: правый ребенок брата черный
                    if (s->right == nullptr || s->right->color == BLACK) {
                        if (s->left != nullptr) s->left->color = BLACK;
                        s->color = RED;
                        rotateRight(s);
                        s = x->parent->right;
                    }
                    // Случай 4: левый ребенок брата черный
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->right != nullptr) s->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = _root;
                }
            }
            else {
                RBTreeNode<T>* s = x->parent->left;
                // Случай 1: брат красный
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    s = x->parent->left;
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
                        if (s->right != nullptr) s->right->color = BLACK;
                        s->color = RED;
                        rotateLeft(s);
                        s = x->parent->left;
                    }
                    // Случай 4: правый ребенок брата черный
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->left != nullptr) s->left->color = BLACK;
                    rotateRight(x->parent);
                    x = _root;
                }
            }
        }
        x->color = BLACK;
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
        if (root == nullptr) return pt;

        if (pt->_value < root->_value) {
            root->left = insertHelper(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->_value > root->_value) {
            root->right = insertHelper(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    void clearHelper(RBTreeNode<T>* node) {
        if (node == nullptr) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

    RBTreeNode<T>* minValueNode(RBTreeNode<T>* node) const {
        RBTreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    RBTreeNode<T>* maxValueNode(RBTreeNode<T>* node) const {
        RBTreeNode<T>* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    RBTreeNode<T>* deleteHelper(RBTreeNode<T>* node, T val) {
        if (node == nullptr) return node;

        if (val < node->_value) {
            return deleteHelper(node->left, val);
        }
        else if (val > node->_value) {
            return deleteHelper(node->right, val);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                return node;
            }
            RBTreeNode<T>* temp = minValueNode(node->right);
            node->_value = temp->_value;
            return deleteHelper(node->right, temp->_value);
        }
    }

    void transplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
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
                SetConsoleTextAttribute(hConsole, 15); // Белый (черный)
                std::cout << "(" << root->_value << ")" << std::endl;
            }
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RBTree() : _root(nullptr) {
        setupConsole();
    }

    ~RBTree() { clear(); }
    // Метод для красивого вывода дерева
    void print() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (_root == nullptr) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "Дерево пусто" << std::endl;
            return;
        }

        // Выводим заголовок
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "Красно-черное дерево:\n";
        std::cout << "R - правое поддерево, L - левое поддерево\n";
        std::cout << "Красные узлы выделены цветом\n\n";

        // Выводим дерево
        _printTree(_root, "", true, hConsole);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

private:
    void _printTree(RBTreeNode<T>* node, const std::string& prefix, bool isLeft, HANDLE hConsole) const {
        if (node == nullptr) return;

        // Выводим текущий узел
        std::cout << prefix;
        std::cout << (isLeft ? "L----" : "R----");

        // Устанавливаем цвет для узла
        if (node->color == RED) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
            std::cout << "[" << node->_value << "]";
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "(" << node->_value << ")";
        }
        std::cout << std::endl;

        // Рекурсивно выводим поддеревья
        _printTree(node->left, prefix + (isLeft ? "|    " : "     "), true, hConsole);
        _printTree(node->right, prefix + (isLeft ? "|    " : "     "), false, hConsole);
    }
    RBTreeNode<T>* getRoot() const { return _root; }

    RBTreeNode<T>* search(T val) const {
        return searchHelper(_root, val);
    }

    void insert(T val) {
        RBTreeNode<T>* node = new RBTreeNode<T>(val);
        _root = insertHelper(_root, node);
        fixInsert(node);
    }

    void erase(T val) {
        RBTreeNode<T>* z = search(val);
        if (z == nullptr) return;

        RBTreeNode<T>* y = z;
        RBTreeNode<T>* x;
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
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            }
            else {
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
            fixDelete(x);
        }
    }

    void clear() {
        clearHelper(_root);
        _root = nullptr;
    }

    void print() const {
        if (_root == nullptr) {
            std::cout << "Empty tree" << std::endl;
        }
        else {
            printHelper(_root, "", true);
        }
    }

    RBTreeNode<T>* _min() const {
        return minValueNode(_root);
    }

    RBTreeNode<T>* _max() const {
        return maxValueNode(_root);
    }

    void levelOrder() const {
        if (_root == nullptr) return;

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
                SetConsoleTextAttribute(hConsole, 15); // Белый (черный)
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
};