#pragma once
#include <vector>
#include <span>
#include <initializer_list>
#include <stdexcept>
#include <format>

class Matrix {
private:
    std::vector<double> data;
    size_t rows{ 0 };
    size_t cols{ 0 };

public:
    Matrix() = default;
    Matrix(size_t r, size_t c);
    Matrix(size_t r, size_t c, double val);
    Matrix(std::initializer_list<std::initializer_list<double>> init);

    // Static factory methods
    static Matrix zeros(size_t r, size_t c);
    static Matrix ones(size_t r, size_t c);
    static Matrix filled(size_t r, size_t c, double val);
    static Matrix identity(size_t n);

    // Access methods
    double& operator()(size_t i, size_t j);
    const double& operator()(size_t i, size_t j) const;
    std::span<double> row(size_t i);
    std::span<const double> row(size_t i) const;

    // Getters
    size_t nRows() const;
    size_t nCols() const;
    size_t size() const;
    bool empty() const;

    // Matrix operations
    Matrix multiply(const Matrix& m) const;
    Matrix add(const Matrix& m) const;
    Matrix subtract(const Matrix& m) const;
    double dot(const Matrix& m) const;

    // Scalar operations
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    // Printing
    void print() const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

// Global operators
Matrix operator*(const Matrix& A, const Matrix& B);
Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, const Matrix& B);
Matrix operator*(double scalar, const Matrix& A);