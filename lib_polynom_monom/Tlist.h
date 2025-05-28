#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_
#include <iostream>
#include <stdexcept>
using namespace std;
template <class T>
class TNode {
    T _value;
    TNode<T>* _pnext;

public:
    TNode(const T& value, TNode<T>* next = nullptr) :
        _value(value), _pnext(next) {}

    T getValue() const { return _value; }
    void setValue(const T& value) { _value = value; }

    TNode<T>* getNext() const { return _pnext; }
    void setNext(TNode<T>* next) { _pnext = next; }

    friend ostream& operator<<(ostream& os, const TNode<T>& node) {
        os << node._value;
        return os;
    }

    friend istream& operator>>(istream& is, TNode<T>& node) {
        is >> node._value;
        return is;
    }

};
template <class T>
class TList {
    TNode<T>* _head;
    TNode<T>* _tail;
    size_t _size;
public:
    TList() : _head(nullptr), _tail(nullptr) {}

    ~TList() {
        clear();
    }

    TList(const TList<T>& other) : _head(nullptr), _tail(nullptr) {
        TNode<T>* current = other._head;
        while (current) {
            pushBack(current->getValue());
            current = current->getNext();
        }
    }

    TList<T>& operator=(const TList<T>& other) {
        if (this != &other) {
            clear();
            TNode<T>* current = other._head;
            while (current) {
                pushBack(current->getValue());
                current = current->getNext();
            }
        }
        return *this;
    }

    void clear() {
        while (_head) {
            removeFirst();
        }
    }

    bool isEmpty() const {
        return _head == nullptr;
    }

    void pushFront(const T& value) {
        TNode<T>* newNode = new TNode<T>(value, _head);
        if (_tail == nullptr) {
            _tail = newNode;
        }
        _head = newNode;
        _size++;
    }


    void pushBack(const T& value) {
        TNode<T>* newNode = new TNode<T>(value);
        if (_head != nullptr) {
            _tail->setNext(newNode);
        }
        else {
            _head = newNode;
        }
        _tail = newNode;
        _size++;
    }
    void insert_2(const CMonom& value, int index) {
        if (index < 0) throw out_of_range("Incorrect index");
        if (index == 0) {
            pushFront(value);
            return;
        }

        TNode<CMonom>* t = _head;
        for (int i = 0; i < index - 1 && t != nullptr; ++i) {
            t = t->getNext();
        }
        if (t) {
            insertAfter(t, value);
        }
        else {
            throw out_of_range("Incorrect index");
        }
    }
    bool insertAfter_2(TNode<CMonom>* p, const CMonom& value) {
        if (!p) return false;
        TNode<CMonom>* newNode = new TNode<CMonom>(value, p->getNext());
        p->setNext(newNode);
        if (newNode->getNext() == nullptr) {
            _tail = newNode;
        }
        return true;
    }

    bool insertAfter(TNode<T>* p, const T& value) {
        if (!p) return false;
        TNode<T>* newNode = new TNode<T>(value, p->getNext());
        p->setNext(newNode);
        if (newNode->getNext() == nullptr) {
            _tail = newNode;
        }
        return true;
    }

    void insert(const T& value, int index) {
        if (index < 0) throw out_of_range("Incorrect index");
        if (index == 0) {
            pushFront(value);
            return;
        }

        TNode<T>* t = _head;
        for (int i = 0; i < index - 1 && t != nullptr; ++i) {
            t = t->getNext();
        }
        if (t) {
            insertAfter(t, value);
        }
        else {
            throw out_of_range("Incorrect index");
        }
    }

    TNode<T>* find(const T& value) {
        TNode<T>* t = _head;
        while (t != nullptr) {
            if (t->getValue() == value) {
                return t;
            }
            t = t->getNext();
        }
        return nullptr;
    }

    TNode<T>* getNode(int index) {
        if (index < 0) throw out_of_range("Incorrect index");
        TNode<T>* p = _head;
        for (int i = 0; i < index && p != nullptr; ++i) {
            p = p->getNext();
        }
        if (p == nullptr) {
            throw out_of_range("Incorrect index");
        }
        return p;
    }
    TNode<T>* head() const {
        return _head;
    }

    void removeFirst() {
        if (_head == nullptr) throw runtime_error("List is empty");
        TNode<T>* t = _head;
        _head = _head->getNext();
        delete t;
        _size--;
        if (_head == nullptr) {
            _tail = nullptr;
        }
    }


    void removeLast() {
        if (_head == nullptr) throw runtime_error("List is empty");
        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            _size--;
        }
        else {
            TNode<T>* t = _head;
            while (t->getNext() != _tail) {
                t = t->getNext();
            }
            delete _tail;
            t->setNext(nullptr);
            _tail = t;
            _size--;
        }
    }


    bool removeNode(TNode<T>* t) {
        if (t == _head) {
            removeFirst();
            return true;
        }
        else if (t == _tail) {
            removeLast();
            return true;
        }
        else {
            TNode<T>* p = _head;
            while (p != nullptr && p->getNext() != t) {
                p = p->getNext();
            }
            if (p != nullptr) {
                p->setNext(t->getNext());
                delete t;
                return true;
            }
            return false;
        }
    }

    void removeBy(int index) {
        if (index < 0) throw out_of_range("Incorrect index");
        if (index == 0) {
            removeFirst();
            return;
        }

        TNode<T>* t = _head;
        for (int i = 0; i < index - 1 && t != nullptr; ++i) {
            t = t->getNext();
        }
        if (t == nullptr || t->getNext() == nullptr) {
            throw out_of_range("Incorrect index");
        }

        if (t->getNext() == _tail) {
            removeLast();
        }
        else {
            TNode<T>* next = t->getNext();
            t->setNext(next->getNext());
            delete next;
        }
    }
    int size() const {
        return _size;
    }

    bool replaceNode(TNode<T>* p, const T& new_value) {
        if (!p) return false;
        p->setValue(new_value);
        return true;
    }

    void replaceBy(int index, const T& new_value) {
        if (index < 0) throw out_of_range("Incorrect index");
        TNode<T>* p = _head;
        for (int i = 0; i < index && p != nullptr; ++i) {
            p = p->getNext();
        }
        if (p == nullptr) {
            throw out_of_range("Incorrect index");
        }
        else {
            p->setValue(new_value);
        }
    }

    class Iterator {
        TNode<T>* _current;
    public:
        Iterator(TNode<T>* start) : _current(start) {}
        Iterator(const Iterator& other) : _current(other._current) {}

        T operator*() const {
            return _current->getValue();
        }
        T operator*() {
            return _current->getValue();
        }

        Iterator& operator++() {
            _current = _current->getNext();
            return *this;
        }
        Iterator& operator++(int) {
            Iterator temp = *this;
            _current = _current->getNext();
            return temp;
        }

        bool operator!=(const Iterator& other) const {
            return _current != other._current;
        }
    };
    typedef Iterator const_iterator;
    typedef Iterator iterator;

    const_iterator begin() const {
        return Iterator(_head);
    }

    const_iterator end() const {
        return Iterator(nullptr);
    }
    Iterator begin() {
        return Iterator(_head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

};
#endif

