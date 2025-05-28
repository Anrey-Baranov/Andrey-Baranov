#ifndef CPOLINOM_H_
#define CPOLINOM_H_

#include <iostream>
#include <algorithm>
#include <string>
#include "CMonom.h"
#include <exception>
#include "TList.h"
#include "TDmassive.h"

class CPolinom {
public:
    size_t _size;
    char* _names;
    TList<CMonom> _monoms;

    CPolinom(std::string str, size_t size) {
        _size = size;
        _names = new char[_size];
        fillVar();
        parse(str);
    }

    CPolinom(const char* mas, size_t size) {
        _size = size;
        _names = new char[_size];
        fillVar();
        parse(std::string(mas));
    }

    CPolinom(size_t size) {
        _size = size;
        _names = new char[_size];
        fillVar();
    }

    CPolinom() {
        _size = 3;
        _names = new char[_size];
        fillVar();
    }

    CPolinom& operator=(const CPolinom& obj) {
        if (this != &obj) {
            delete[] _names;
            _size = obj._size;
            _names = new char[_size];
            std::copy(obj._names, obj._names + _size, _names);
            _monoms = obj._monoms;
        }
        return *this;
    }

    CPolinom(const CPolinom& obj) {
        _size = obj._size;
        _names = new char[_size];
        std::copy(obj._names, obj._names + _size, _names);
        _monoms = obj._monoms;
    }

    void fillVar() {
        for (size_t i = 97; i < 97 + _size; i++) {
            _names[i - 97] = static_cast<char>(i);
        }
    }

    ~CPolinom() {
        delete[] _names;
    }

    void parse(std::string str) {
        TDMassive<std::string> list;
        std::string monom;
        for (auto it = str.begin(); it != str.end(); it++) {
            if ((*it) == '+' || (*it) == '-') {
                if (!monom.empty()) {
                    list.push_back(monom);
                }
                monom = (*it); // Сохраняем знак
            }
            else if ((*it) == '*' || (*it) == '/') {
                if (!monom.empty()) {
                    list.push_back(monom);
                }
                list.push_back(std::string(1, (*it)));
                monom.clear();
            }
            else {
                monom += (*it);
            }
        }
        if (!monom.empty()) {
            list.push_back(monom);
        }

        for (size_t i = 0; i < list.size(); i++) {
            if (list[i + 1] == "*" || list[i + 1] == "/") {
                if (list[i + 1] == "*") {
                    appendPolinom(CMonom(list[i], _names, _size) * CMonom(list[i + 2], _names, _size));
                }
                else {
                    appendPolinom(CMonom(list[i], _names, _size) / CMonom(list[i + 2], _names, _size));
                }
                i += 2; 
            }
            else {
                appendPolinom(CMonom(list[i], _names, _size));
            }
        }
        this->calculate(); 
    }
    void appendPolinom(const CMonom& obj) {
        if (_monoms.isEmpty()) {
            _monoms.pushBack(obj);
        }
        else {
            size_t index = 0;
            bool flag = false;
            for (auto it = _monoms.begin(); it != _monoms.end(); it++, index++) {
                if (obj > *it || obj == *it) { 
                    _monoms.insert_2(obj, static_cast<int>(index));
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                _monoms.pushBack(obj);
            }
        }
    }

    void calculate() {
        auto cur = _monoms.begin();
        auto next = _monoms.begin(); next++;
        CPolinom pol(_size);
        CMonom mon = (*cur);
        while (cur != _monoms.end()) {
            if (next != _monoms.end() && (*cur) == (*next)) {
                mon = (*cur);
                mon += (*next);
            }
            else {
                if (!mon.is_null())
                    pol.appendPolinom(mon);
                if (next != _monoms.end()) {
                    cur = next;
                    mon = (*cur);
                }
                else
                    break;
            }
            next++;
        }
        (*this) = pol;
    }

    double valuePoint(const double* points) {
        double result = 0;
        for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
            result += (*it).valuePoint(points); 
        }
        return result;
    }



    CPolinom operator+(const CMonom& obj) const {
        if (obj._size != _size)
            throw std::logic_error("incorrect addition of polynomials");
        CPolinom polinom(*this);
        polinom.appendPolinom(obj);
        polinom.calculate();
        return polinom;
    }

    CPolinom& operator+=(const CMonom& obj) {
        if (obj._size != _size)
            throw std::logic_error("incorrect addition of polynomials");
        this->appendPolinom(obj);
        this->calculate();
        return *this;
    }

    CPolinom operator-(const CMonom& obj) const {
        if (obj._size != _size)
            throw std::logic_error("incorrect addition of polynomials");
        CPolinom polinom(*this);
        polinom.appendPolinom(obj * (-1));
        polinom.calculate();
        return polinom;
    }
    bool operator==(const CPolinom& obj) const {
        if (_size != obj._size || _monoms.size() != obj._monoms.size()) {
            return false;
        }
        auto it1 = _monoms.begin();
        auto it2 = obj._monoms.begin();
        while (it1 != _monoms.end() && it2 != obj._monoms.end()) {
            if (!(*it1 == *it2)) { // Предполагается, что CMonom также имеет перегруженный оператор ==
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }

    CPolinom& operator-=(const CMonom& obj) {
        if (obj._size != _size)
            throw std::logic_error("incorrect addition of polynomials");
        this->appendPolinom(obj * (-1));
        this->calculate();
        return *this;
    }

    CPolinom operator*(const CMonom& obj) const {
        CPolinom polinom(std::max(_size, obj._size));
        for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
            polinom.appendPolinom((*it) * obj);
        }
        polinom.calculate();
        return polinom;
    }

    CPolinom& operator*=(const CMonom& obj) {
        if (_size != obj._size) {
            _size = std::max(_size, obj._size);
            this->fillVar();
        }
        for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
            this->appendPolinom((*it) * obj);
        }
        this->calculate();
        return *this;
    }

    CPolinom operator/(const CMonom& obj) const {
        CPolinom polinom(std::max(_size, obj._size));
        for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
            polinom.appendPolinom((*it) / obj);
        }
        polinom.calculate();
        return polinom;
    }

    CPolinom& operator/=(const CMonom& obj) {
        if (_size != obj._size) {
            _size = std::max(_size, obj._size);
            this->fillVar();
        }
        for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
            this->appendPolinom((*it) / obj);
        }
        this->calculate();
        return *this;
    }

    CPolinom operator+(const CPolinom& obj) const {
        if (_size != obj._size)
            throw std::logic_error("incorrect addition of polynomials");
        CPolinom polinom = (*this);
        for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
            polinom = polinom + (*it);
        }
        return polinom;
    }

    CPolinom& operator+=(const CPolinom& obj) {
        if (_size != obj._size)
            throw std::logic_error("incorrect addition of polynomials");
        for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
            (*this) += (*it);
        }
        return *this;
    }

    CPolinom operator-(const CPolinom& obj) const {
        if (_size != obj._size)
            throw std::logic_error("incorrect addition of polynomials");
        CPolinom polinom = (*this);
        for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
            polinom = polinom - (*it);
        }
        return polinom;
    }
    // Перегрузка оператора унарного минуса
    CPolinom operator-() const {
        CPolinom negated(*this); // Создаем копию текущего полинома
        for (auto it = negated._monoms.begin(); it != negated._monoms.end(); ++it) {
            *it = -(*it); // Меняем знак каждого монома
        }
        return negated; // Возвращаем новый полином с изменёнными знаками
    }
    CPolinom& operator-=(const CPolinom& obj) {
        if (_size != obj._size)
            throw std::logic_error("incorrect addition of polynomials");
        for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
            (*this) -= (*it);
        }
        return *this;
    }

    CPolinom operator*(const CPolinom& obj) const {
        CPolinom polinom(std::max(_size, obj._size));
        for (auto it = obj._monoms.begin(); it != obj._monoms.end(); it++) {
            polinom += (*this) * (*it);
        }
        return polinom;
    }

    CPolinom operator/(const CPolinom& obj) const {
        CPolinom polinom(std::max(_size, obj._size));
        CPolinom copy = (*this);
        CMonom obj_head = obj._monoms.head()->getValue();
        while (!copy._monoms.isEmpty() && (copy._monoms.head()->getValue() > obj_head || copy._monoms.head()->getValue() == obj_head)) {
            CMonom copy_head = copy._monoms.head()->getValue();
            CMonom del = copy_head / obj_head;
            copy -= obj * del;
            polinom.appendPolinom(del);
        }
        return polinom;
    }


    bool isVariable(const CMonom& obj) const {
        for (size_t i = 0; i < obj._size; i++) {
            if (obj._powers[i] != 0)
                return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const CPolinom& polinom) {
        auto next = polinom._monoms.begin(); next++;
        for (auto it = polinom._monoms.begin(); it != polinom._monoms.end(); it++) {
            if ((*it)._coef == -1) {
                out << "-";
                if (polinom.isVariable((*it)) == false)
                    out << "1";
            }
            else if ((*it)._coef == 1) {
                if (it != polinom._monoms.begin())
                    out << "+";
                if (polinom.isVariable((*it)) == false)
                    out << "1";
            }
            else {
                if ((it != polinom._monoms.begin()) && (*it)._coef > 0)
                    out << "+";
                out << (*it)._coef;
            }
            for (size_t i = 0; i < polinom._size; i++) {
                if ((*it)._powers[i] != 0) {
                    if ((*it)._powers[i] == 1)
                        out << polinom._names[i];
                    else
                        out << polinom._names[i] << "^" << (*it)._powers[i];
                }
            }
            if (next != polinom._monoms.end()) {
                next++;
            }
        }
        out << std::endl;
        return out;
    }
};

#endif