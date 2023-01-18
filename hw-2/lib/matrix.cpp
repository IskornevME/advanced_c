#include "matrix.h"
#include "vector.h"
#include <math.h>

#include <stdexcept>
#include <algorithm>
#include <iostream>

static constexpr double EPS = 1e-10;

Matrix::Matrix()
    : _row(0)
    , _col(0)
    , _data(nullptr)
{}

Matrix::Matrix(size_t row, size_t col)
    : _row(row)
    , _col(col)
    , _data(std::make_unique<double[]>(row * col))
{}

Matrix::Matrix(const Matrix &rhs)
    : _row(rhs._row)
    , _col(rhs._col)
    , _data(std::make_unique<double[]>(_row * _col)) {
    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] = rhs._data[i];
    }
}

Matrix::Matrix(Matrix &&rhs)
    : _row(rhs._row)
    , _col(rhs._col)
    , _data(std::move(rhs._data))

{}

Matrix::Matrix(const std::vector<double> &rhs, size_t row, size_t col) {
    if (row * col != rhs.size()) {
        throw std::invalid_argument("Incorrect vector len");
    }

    _row = row;
    _col = col;
    _data = std::make_unique<double[]>(_row * _col);

    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] = rhs[i];
    }
}

Matrix::Matrix(const std::vector<Vector> &rhs) {
    if (rhs.empty()) {
        throw std::invalid_argument("Incorrect data len");
    }

    size_t row = rhs.size();
    size_t col = rhs[0].size();

    for (size_t i = 1; i < row; i++) {
        if (rhs[i].size() != col) {
            throw std::invalid_argument("Incorrect data len");
        }
    }

    _row = row;
    _col = col;
    _data = std::make_unique<double[]>(_row * _col);

    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            this->at(i, j) = rhs[i][j];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (this == &rhs) {
        return *this;
    }

    _data = std::make_unique<double[]>(rhs._row * rhs._col);
    _row = rhs._row;
    _col = rhs._col;

    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] = rhs._data[i];
    }

    return *this;
}

Matrix &Matrix::operator=(Matrix &&rhs) {
    if (this == &rhs) {
        return *this;
    }

    _row = rhs._row;
    _col = rhs._col;
    _data = std::move(rhs._data);

    return *this;
}

double &Matrix::at(size_t i, size_t j) {
    if (i >= _row) {
        throw std::out_of_range("Index out of range. Incorrent row number");
    }
    if (j >= _col) {
        throw std::out_of_range("Index out of range. Incorrent column number");
    }
    return _data[i * _col + j];
}

double Matrix::at(size_t i, size_t j) const {
    if (i >= _row) {
        throw std::out_of_range("Index out of range. Incorrent row number");
    }
    if (j >= _col) {
        throw std::out_of_range("Index out of range. Incorrent column number");
    }
    return _data[i * _col + j];
}

Vector Matrix::get_row(size_t i) const {
    Vector res {_col};

    for (size_t j = 0; j < _col; j++) {
        res[j] = this->at(i, j);
    }

    return res;
}

Vector Matrix::get_col(size_t j) const {
    Vector res {_row};

    for (size_t i = 0; i < _row; i++) {
        res[i] = this->at(i, j);
    }

    return res;
}

Vector Matrix::get_diag() const {
    size_t min_dim = std::min(_row, _col);
    Vector res {min_dim};

    for (size_t i = 0; i < min_dim; i++) {
        res[i] = this->at(i, i);
    }

    return res;
}

size_t Matrix::row() const {
    return _row;
}

size_t Matrix::col() const {
    return _col;
}

const Matrix &Matrix::operator+() const {
    return *this;
}

Matrix &Matrix::operator+() {
    return *this;
}

Matrix Matrix::operator-() const {
    return (*this) * (-1);
}

Matrix &Matrix::operator+=(const Matrix &rhs) {
    if (_row != rhs._row || _col != rhs._col) {
        throw std::invalid_argument("Different matrix sizes");
    }

    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] += rhs._data[i];
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs) {
    if (_row != rhs._row || _col != rhs._col) {
        throw std::invalid_argument("Different matrix sizes");
    }

    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] -= rhs._data[i];
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &rhs) {
    if (_row != rhs._row || _col != rhs._col) {
        throw std::invalid_argument("Different matrix sizes");
    }

    for (size_t i = 0; i < _row * _col; i++) {
        _data[i] *= rhs._data[i];
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    Matrix tmp {*this};
    tmp += rhs;
    return tmp;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
    Matrix tmp {*this};
    tmp -= rhs;
    return tmp;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    Matrix tmp {*this};
    tmp *= rhs;
    return tmp;
}

Matrix &Matrix::add_assign(const Vector &rhs, size_t axis) {
    if (axis == 0) {
        if (_col != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _row; i++) {
            for (size_t j = 0; j < _col; j++) {
                this->at(i, j) += rhs[j];
            }
        }

        return *this;
    } else if (axis == 1) {
        if (_row != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _row; i++) {
            for (size_t j = 0; j < _col; j++) {
                this->at(i, j) += rhs[i];
            }
        }

        return *this;
    } else {
        throw std::invalid_argument("Incorrect axis");
    }
}

Matrix &Matrix::sub_assign(const Vector &rhs, size_t axis) {
    if (axis == 0) {
        if (_col != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _row; i++) {
            for (size_t j = 0; j < _col; j++) {
                this->at(i, j) -= rhs[j];
            }
        }

        return *this;
    } else if (axis == 1) {
        if (_row != rhs.size()) {
            throw std::invalid_argument("Incorrect vector size");
        }

        for (size_t i = 0; i < _row; i++) {
            for (size_t j = 0; j < _col; j++) {
                this->at(i, j) -= rhs[i];
            }
        }

        return *this;
    } else {
        throw std::invalid_argument("Incorrect axis");
    }
}

Matrix Matrix::add(const Vector &rhs, size_t axis) const {
    Matrix tmp {*this};
    tmp.add_assign(rhs, axis);
    return tmp;
}

Matrix Matrix::sub(const Vector &rhs, size_t axis) const {
    Matrix tmp {*this};
    tmp.sub_assign(rhs, axis);
    return tmp;
}

Vector Matrix::mult(const Vector &rhs) const {
    if (_col != rhs.size()) {
        throw std::invalid_argument("Vector has incorrect size");
    }

    Vector res {_row};

    for (size_t i = 0; i < _row; i++) {
        res[i] = 0;
        for (size_t j = 0; j < _col; j++) {
            res[i] += this->at(i, j) * rhs[j];
        }
    }

    return res;
}

Matrix &Matrix::operator+=(double rhs) {
    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            this->at(i, j) += rhs;
        }
    }

    return *this;
}

Matrix &Matrix::operator-=(double rhs) {
    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            this->at(i, j) -= rhs;
        }
    }

    return *this;
}

Matrix &Matrix::operator*=(double rhs) {
    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            this->at(i, j) *= rhs;
        }
    }

    return *this;
}

Matrix Matrix::operator+(double rhs) const {
    Matrix tmp {*this};
    tmp += rhs;
    return tmp;
}

Matrix Matrix::operator-(double rhs) const {
    Matrix tmp {*this};
    tmp -= rhs;
    return tmp;
}

Matrix Matrix::operator*(double rhs) const {
    Matrix tmp {*this};
    tmp *= rhs;
    return tmp;
}

Matrix Matrix::mult_matrix(const Matrix &rhs) const {
    if (_col != rhs.row()) {
        throw std::invalid_argument("Matricies have incorrect size");
    }

    Matrix res {_row, rhs.col()};

    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < rhs.col(); j++) {
            double tmp = 0;
            for (size_t k = 0; k < _col; k++) {
                tmp += this->at(i, k) * rhs.at(k, j);
            }
            res.at(i, j) = tmp;
        }
    }

    return res;
}

Matrix Matrix::transpose() const {
    Matrix res {_col, _row};

    for (size_t i = 0; i < _col; i++) {
        for (size_t j = 0; j < _row; j++) {
            res.at(i, j) = this->at(j, i);
        }
    }

    return res;
}

Matrix Matrix::inverse() const {
    if (_row != _col) {
        throw std::invalid_argument("Matrix has incorrent shape");
    }
    Matrix res {_row, _col};

    Matrix I {_row, _col};

    for (size_t i = 0; i < _row; i++) {
        I.at(i, i) = 1;
    }

    Matrix m_all {_row, 2 * _col};

    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            m_all.at(i, j) = this->at(i, j);
        }
    }

    for (size_t i = 0; i < _row; i++) {
        for (size_t j = _col; j < m_all.col(); j++) {
            m_all.at(i, j) = I.at(i, j - _col);
        }
    }

    for (size_t i = 0; i < _row; i++) {
        size_t k = i;
        for (size_t j = i + 1; j < _row; j++) {
            if (fabs(m_all.at(j, i)) > fabs(m_all.at(k, i))) {
                k = j;
            }
        }

        m_all.my_swap(i, k);

        double tmp = m_all.at(i, i);
        if (fabs(tmp) < EPS) {
            throw std::invalid_argument("There is no inverse");
        }
        for (size_t j = i; j < m_all.col(); j++) {
            m_all.at(i, j) /= tmp;
        }
        for (size_t j = 0; j < _row; j++) {
            if (j != i && fabs(m_all.at(j, i)) > EPS) {
                tmp = m_all.at(j, i);
                for (size_t l = i; l < m_all.col(); l++) {
                    m_all.at(j, l) -= m_all.at(i, l) * tmp;
                }
            }
        }
    }

    for (size_t i = 0; i < _row; i++) {
        for (size_t j = 0; j < _col; j++) {
            res.at(i, j) = m_all.at(i, _col + j);
        }
    }

    return res;
}

double Matrix::determinant() const {
    if (_row != _col) {
        throw std::invalid_argument("Matrix has incorrent shape");
    }
    size_t n = _row;
    Matrix mat {*this};

    double det = 1;
    for (size_t i = 0; i < n; i++) {
        size_t k = i;
        for (size_t j = i + 1; j < n; j++) {
            if (fabs(mat.at(j, i)) > fabs(mat.at(k, i))) {
                k = j;
            }
        }

        if (fabs(mat.at(k, i)) < EPS) {
            return 0;
        }

        mat.my_swap(i, k);

        if (i != k) {
            det = -det;
        }
        det *= mat.at(i, i);
        double tmp = mat.at(i, i);
        for (size_t j = i; j < n; j ++) {
            mat.at(i, j) /= tmp;
        }
        for (size_t j = 0; j < n; j++) {
            if (j != i && fabs(mat.at(j, i)) > EPS) {
                for (size_t l = i + 1; l < n; l++) {
                    mat.at(j, l) -= mat.at(i, l) * mat.at(j, i);
                }
            }
        }
    }

    return det;
}

Matrix Matrix::my_swap(size_t i, size_t j) {
    for (size_t k = 0; k < _col; k++) {
        double tmp = this->at(i, k);
        this->at(i, k) = this->at(j, k);
        this->at(j, k) = tmp;
    }
    return *this;
}

Matrix operator+(double lhs, const Matrix &rhs) {
    return rhs + lhs;
}

Matrix operator-(double lhs, const Matrix &rhs) {
    return -(rhs - lhs);
}

Matrix operator*(double lhs, const Matrix &rhs) {
    return rhs * lhs;
}
