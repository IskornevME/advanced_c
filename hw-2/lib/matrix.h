#pragma once // NOLINT

#include <memory>
#include <vector>

class Vector;

class Matrix {
 public:
    Matrix();
    Matrix(size_t row, size_t col);
    Matrix(const Matrix &rhs);
    Matrix(Matrix &&rhs);
    Matrix(const std::vector<double> &rhs, size_t row, size_t col);
    explicit Matrix(const std::vector<Vector> &rhs);

    Matrix &operator=(const Matrix &rhs);
    Matrix &operator=(Matrix &&rhs);

    double &at(size_t i, size_t j);
    double at(size_t i, size_t j) const;

    Vector get_row(size_t i) const;
    Vector get_col(size_t j) const;
    Vector get_diag() const;

    size_t row() const;
    size_t col() const;

    const Matrix &operator+() const;
    Matrix &operator+();
    Matrix operator-() const;

    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(const Matrix &rhs);

    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;

    Matrix &add_assign(const Vector &rhs, size_t axis);
    Matrix &sub_assign(const Vector &rhs, size_t axis);

    Matrix add(const Vector &rhs, size_t axis) const;
    Matrix sub(const Vector &rhs, size_t axis) const;
    Vector mult(const Vector &rhs) const;

    Matrix &operator+=(double rhs);
    Matrix &operator-=(double rhs);
    Matrix &operator*=(double rhs);

    Matrix operator+(double rhs) const;
    Matrix operator-(double rhs) const;
    Matrix operator*(double rhs) const;

    Matrix mult_matrix(const Matrix &rhs) const;

    Matrix transpose() const;
    Matrix inverse() const;
    double determinant() const;

    Matrix my_swap(size_t i, size_t j);

 private:
    size_t _row;
    size_t _col;
    std::unique_ptr<double[]> _data;
};

Matrix operator+(double lhs, const Matrix &rhs);
Matrix operator-(double lhs, const Matrix &rhs);
Matrix operator*(double lhs, const Matrix &rhs);
