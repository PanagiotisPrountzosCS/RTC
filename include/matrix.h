#pragma once

#include <memory>
#include <vector>

#include "tuple.h"

namespace RTC {

class Matrix {
public:
    Matrix(const std::vector<std::vector<float>>& input);
    Matrix(int a, int b);
    Matrix(int n);  // this will return nxn identity
    Matrix();
    Matrix(const Matrix& m);
    ~Matrix();

    bool operator==(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Tuple operator*(const Tuple& rhs) const;
    Matrix operator*(const float& scalar);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs);

    int getRows() const;
    int getCols() const;

    float determinant() const;
    float minor(int i, int j) const;
    float cofactor(int i, int j) const;
    bool isInvertible() const;

    Matrix submatrix(int row, int col) const;
    Matrix inverse() const;
    Matrix transpose();

    float** data;

private:
    int rows;
    int cols;
};

}  // namespace RTC