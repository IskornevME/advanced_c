#include "vector.h"
#include "matrix.h"
#include <stdexcept>

Vector::Vector()
    : _size(0)
    , _data(nullptr)
{}

Vector::Vector(size_t size)
    : _size(size)
    , _data(std::make_unique<double[]>(size))
{}

Vector::Vector(const Vector &rhs)
    : _size(rhs._size)
    , _data(std::make_unique<double[]>(_size)) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs._data[i];
    }
}

Vector::Vector(Vector &&rhs)
    : _size(rhs._size)
    , _data(std::move(rhs._data))
{}

Vector::Vector(const std::vector<double> &rhs)
    : _size(rhs.size())
    , _data(std::make_unique<double[]>(_size)) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs[i];
    }
}

Vector &Vector::operator=(const Vector &rhs) {
    if (this == &rhs) {
        return *this;
    }

    _data = std::make_unique<double[]>(rhs._size);
    _size = rhs._size;

    for (size_t i = 0; i < _size; i++) {
        _data[i] = rhs._data[i];
    }

    return *this;
}

Vector &Vector::operator=(Vector &&rhs) {
    if (this == &rhs) {
        return *this;
    }

    _size = rhs._size;
    _data = std::move(rhs._data);

    return *this;
}

double &Vector::operator[](size_t i) {
    if (i >= _size) {
        throw std::out_of_range("");
    }

    return _data[i];
}

const double &Vector::operator[](size_t i) const {
    if (i >= _size) {
        throw std::out_of_range("");
    }

    return _data[i];
}

size_t Vector::size() const {
    return _size;
}

const Vector &Vector::operator+() const {
    return *this;
}

Vector &Vector::operator+() {
    return *this;
}

Vector Vector::operator-() const {
    return (*this) * (-1);
}

Vector &Vector::operator+=(const Vector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Different vectors sizes");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] += rhs._data[i];
    }

    return *this;
}

Vector &Vector::operator-=(const Vector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Different vectors sizes");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] -= rhs._data[i];
    }

    return *this;
}

Vector &Vector::operator*=(const Vector &rhs) {
    if (_size != rhs._size) {
        throw std::invalid_argument("Different vectors sizes");
    }

    for (size_t i = 0; i < _size; i++) {
        _data[i] *= rhs._data[i];
    }

    return *this;
}

Vector Vector::operator+(const Vector &rhs) const {
    Vector tmp {*this};
    tmp += rhs;
    return tmp;
}

Vector Vector::operator-(const Vector &rhs) const {
    Vector tmp {*this};
    tmp -= rhs;
    return tmp;
}

Vector Vector::operator*(const Vector &rhs) const {
    Vector tmp {*this};
    tmp *= rhs;
    return tmp;
}

Vector &Vector::operator+=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] += rhs;
    }

    return *this;
}

Vector &Vector::operator-=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] -= rhs;
    }

    return *this;
}

Vector &Vector::operator*=(const double &rhs) {
    for (size_t i = 0; i < _size; i++) {
        _data[i] *= rhs;
    }

    return *this;
}

Vector Vector::operator+(const double &rhs) const {
    Vector tmp {*this};
    tmp += rhs;
    return tmp;
}

Vector Vector::operator-(const double &rhs) const {
    Vector tmp {*this};
    tmp -= rhs;
    return tmp;
}

Vector Vector::operator*(const double &rhs) const {
    Vector tmp {*this};
    tmp *= rhs;
    return tmp;
}

Vector Vector::mult(const Matrix &rhs) const {
    if (_size != rhs.row()) {
        throw std::invalid_argument("Matrix has incorrect size");
    }

    Vector res {rhs.col()};

    for (size_t j = 0; j < rhs.col(); j++) {
        res[j] = 0;
        for (size_t i = 0; i < rhs.row(); i ++) {
            res[j] += rhs.at(i, j) * _data[i];
        }
    }

    return res;
}

Vector operator+(const double &lhs, const Vector &rhs) {
    return rhs + lhs;
}

Vector operator-(const double &lhs, const Vector &rhs) {
    return -(rhs - lhs);
}

Vector operator*(const double &lhs, const Vector &rhs) {
    return rhs * lhs;
}
