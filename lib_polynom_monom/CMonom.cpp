#include "CMonom.h"

CMonom::CMonom(size_t size) {
    _size = size;
    _coef = 0;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = 0;
    }
}

CMonom::CMonom(const std::string& str, char* names, size_t size) {
    _size = size;
    _powers = new int[_size];
    int curr_pos = 0;
    double result = 0;
    int sign = 1;

    if (str.empty()) {
        throw std::invalid_argument("Input string is empty");
    }


    if (str[0] == '-') {
        sign = -1;
        curr_pos = 1;
    }
    else if (str[0] == '+') {
        curr_pos = 1;
    }


    if (is_number(str[curr_pos])) {
        while (curr_pos < str.length() && is_number(str[curr_pos])) {
            result = result * 10 + (str[curr_pos] - '0');
            curr_pos++;
        }
        if (curr_pos < str.length() && str[curr_pos] == '.') {
            curr_pos++;
            double double_part = 0.0;
            int accuracy = 0;
            while (curr_pos < str.size() && is_number(str[curr_pos])) {
                double_part = double_part * 10 + (str[curr_pos] - '0');
                curr_pos++;
                accuracy++;
            }
            result += double_part * pow(10, -accuracy);
        }
    }
    else {
        result = 1;
    }
    result *= sign;
    _coef = result;

    for (size_t i = 0; i < _size; i++) {
        size_t index = str.find(names[i]);
        if (index != std::string::npos) {
            if (index + 2 < str.size() && is_number(str[index + 2])) {
                result = 0;
                index += 2;
                while (index < str.size() && is_number(str[index])) {
                    result = result * 10 + (str[index] - '0');
                    index++;
                }
                _powers[i] = static_cast<int>(result);
            }
            else {
                _powers[i] = 1;
            }
        }
        else {
            _powers[i] = 0;
        }
    }
}

bool CMonom::is_number(const char& symbol) const noexcept {
    return symbol >= '0' && symbol <= '9';
}

bool CMonom::is_null() const noexcept {
    return _coef == 0;
}

CMonom::CMonom(const CMonom& monom) {
    _size = monom._size;
    _coef = monom._coef;
    _powers = new int[_size];
    std::copy(monom._powers, monom._powers + _size, _powers);
}

CMonom::CMonom(double coef, int* mas, size_t size) {
    _coef = coef;
    _size = size;
    _powers = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _powers[i] = mas[i];
    }
}

CMonom::CMonom(double coef, size_t size) {
    _coef = coef;
    _size = size;
    _powers = new int[_size];
}

CMonom& CMonom::operator=(const CMonom& obj) {
    if (this != &obj) {
        _coef = obj._coef;
        _size = obj._size;
        delete[] _powers;
        _powers = new int[_size];
        std::copy(obj._powers, obj._powers + _size, _powers);
    }
    return *this;
}

CMonom::~CMonom() {
    delete[] _powers;
}

CMonom CMonom::operator+(const CMonom& obj) const {
    if (_size != obj._size)
        throw std::logic_error("addition of monomials with different sizes");
    CMonom monom = CMonom(_coef + obj._coef, _powers, _size);
    return monom;
}

CMonom& CMonom::operator+=(const CMonom& obj) {
    if (_size != obj._size || (*this) != obj)
        throw std::logic_error("addition of monomials with different sizes");
    _coef += obj._coef;
    return *this;
}

CMonom CMonom::operator-(const CMonom& obj) const {
    if (_size != obj._size)
        throw std::logic_error("addition of monomials with different sizes");
    CMonom monom = CMonom(_coef - obj._coef, _powers, _size);
    return monom;
}


CMonom CMonom::operator*(const CMonom& obj) const noexcept {
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef * obj._coef, max);
    for (size_t i = 0; i < max; i++) {
        if (_size <= i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size <= i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] + obj._powers[i];
    }
    return monom;
}
CMonom& CMonom::operator*=(const CMonom& obj) noexcept {

    _coef *= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];
    }
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] += obj._powers[i];
    }
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator/(const CMonom& obj) const {
    if (obj._coef == 0)
        throw std::logic_error("you can't divide by zero");
    size_t max = std::max(_size, obj._size);
    CMonom monom = CMonom(_coef / obj._coef, max);
    for (size_t i = 0; i < max; i++) {
        if (_size <= i)
            monom._powers[i] = obj._powers[i];
        else if (obj._size <= i)
            monom._powers[i] = _powers[i];
        else
            monom._powers[i] = _powers[i] - obj._powers[i];
    }
    return monom;
}

CMonom& CMonom::operator/=(const CMonom& obj) {
    if (obj._coef == 0)
        throw std::logic_error("you can't divide by zero");
    _coef /= obj._coef;
    size_t max = std::max(_size, obj._size);
    int* mas = new int[max];
    for (size_t i = 0; i < _size; i++) {
        mas[i] = _powers[i];
    }
    for (size_t i = 0; i < obj._size; i++) {
        mas[i] -= obj._powers[i];
    }
    delete[] _powers;
    _powers = mas;
    _size = max;
    return *this;
}

CMonom CMonom::operator*(const double& value) const noexcept {
    return CMonom(value * _coef, _powers, _size);
}

CMonom& CMonom::operator*=(const double& value) noexcept {
    this->_coef *= value;
    return *this;
}

CMonom CMonom::operator/(const double& value) const {
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    return CMonom(_coef / value, _powers, _size);
}

CMonom& CMonom::operator/=(const double& value) {
    if (value == 0)
        throw std::logic_error("you can't divide by zero");
    this->_coef /= value;
    return *this;
}

CMonom CMonom::operator-() const noexcept {
    return CMonom(-_coef, _powers, _size);
}

int CMonom::getDegrees() const {
    int maxDegree = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_powers[i] > maxDegree) {
            maxDegree = _powers[i];
        }
    }
    return maxDegree;
}


bool CMonom::operator==(const CMonom& obj) const noexcept {
    if (_size != obj._size) {
        return false;
    }
    for (size_t i = 0; i < _size; i++) {
        if (_powers[i] != obj._powers[i]) {
            return false;
        }
    }
    return _coef == obj._coef;
}

bool CMonom::operator!=(const CMonom& obj) const noexcept {
    return !((*this) == obj);
}
bool CMonom::isEqual(const CMonom& other) const noexcept {

    if (_size != other._size) {
        return false;
    }

    for (size_t i = 0; i < _size; i++) {
        if (_powers[i] != other._powers[i]) {
            return false;
        }
    }

    return _coef == other._coef;
}


bool CMonom::operator>(const CMonom& obj) const noexcept {
    if (_size != obj._size) {
        return _size > obj._size;
    }
    for (size_t i = 0; i < _size; i++) {
        if (_powers[i] != obj._powers[i]) {
            return _powers[i] > obj._powers[i];
        }
    }
    return _coef > obj._coef;
}

bool CMonom::operator<(const CMonom& obj) const noexcept {
    return !((*this) > obj) && (*this) != obj;
}

double CMonom::valuePoint(const double* point) const noexcept {
    double result = _coef;
    for (size_t i = 0; i < _size; i++) {
        result *= std::pow(point[i], _powers[i]);
    }
    return result;
}
