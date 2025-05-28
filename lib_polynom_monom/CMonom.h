#ifndef CMONOM_H_
#define CMONOM_H_
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>

class CMonom {
public:
    double _coef;
    int* _powers;
    size_t _size;
    CMonom(size_t size);
    CMonom(const std::string& str, char* names, size_t size);
    CMonom(double coef, int* mas, size_t size);
    CMonom(double coef, size_t size);
    CMonom(const CMonom& monom);
    ~CMonom();
    CMonom() : _coef(0), _powers(nullptr), _size(0) {}

    CMonom& operator=(const CMonom& obj);

    friend std::istream& operator>>(std::istream& in, CMonom& monom) {
        size_t size; double coef;
        std::cout << "size: "; in >> size; monom._size = size;
        std::cout << "coef: "; in >> coef; monom._coef = coef;
        monom._powers = new int[monom._size];
        for (size_t i = 0; i < monom._size; i++) {
            std::cout << "[" << i << "]" << " = "; in >> monom._powers[i];
        }
        std::cout << std::endl;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& os, const CMonom& monom) {
        os << "coef: " << monom._coef << std::endl;
        os << "Degrees: ";
        for (size_t i = 0; i < monom._size; i++) {
            os << monom._powers[i];
            if (i < monom._size - 1)
                os << ", ";
        }
        os << std::endl;
        return os;
    }

    bool is_number(const char& symbol) const noexcept;
    bool is_null() const noexcept;
    int getDegrees() const;

    CMonom operator+(const CMonom& obj) const;
    CMonom& operator+=(const CMonom& obj);

    CMonom operator-(const CMonom& obj) const;
    CMonom& operator-=(const CMonom& obj);

    CMonom operator*(const CMonom& obj) const noexcept;
    CMonom& operator*=(const CMonom& obj) noexcept;

    CMonom operator/(const CMonom& obj) const;
    CMonom& operator/=(const CMonom& obj);

    CMonom operator*(const double& value) const noexcept;
    CMonom& operator*=(const double& value) noexcept;

    CMonom operator/(const double& value) const;
    CMonom& operator/=(const double& value);

    CMonom operator-() const noexcept;

    bool operator==(const CMonom& obj) const noexcept;
    bool operator!=(const CMonom& obj) const noexcept;
    bool isEqual(const CMonom& other) const noexcept;
    bool operator>(const CMonom& obj) const noexcept;
    bool operator<(const CMonom& obj) const noexcept;

    double valuePoint(const double* point) const noexcept;
};

#endif // CMONOM_H_