#pragma once // NOLINT

#include <memory>
#include <vector>

class Matrix;

class Vector {
 public:
    Vector();
    explicit Vector(size_t size);
    Vector(const Vector &rhs);
    Vector(Vector &&rhs);
    explicit Vector(const std::vector<double> &rhs);

    Vector &operator=(const Vector &rhs);
    Vector &operator=(Vector &&rhs);

    double &operator[](size_t i);
    const double &operator[](size_t i) const;

    size_t size() const;

    const Vector &operator+() const;
    Vector &operator+();
    Vector operator-() const;

    Vector &operator+=(const Vector &rhs);
    Vector &operator-=(const Vector &rhs);
    Vector &operator*=(const Vector &rhs);

    Vector operator+(const Vector &rhs) const;
    Vector operator-(const Vector &rhs) const;
    Vector operator*(const Vector &rhs) const;

    Vector &operator+=(const double &rhs);
    Vector &operator-=(const double &rhs);
    Vector &operator*=(const double &rhs);

    Vector operator+(const double &rhs) const;
    Vector operator-(const double &rhs) const;
    Vector operator*(const double &rhs) const;

    Vector mult(const Matrix &rhs) const;

 private:
    size_t _size;
    std::unique_ptr<double[]> _data;
};

Vector operator+(const double &lhs, const Vector &rhs);
Vector operator-(const double &lhs, const Vector &rhs);
Vector operator*(const double &lhs, const Vector &rhs);
