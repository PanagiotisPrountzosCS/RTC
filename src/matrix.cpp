#include <iostream>
#include <vector>

#include "algorithms.h"
#include "matrix.h"

namespace RTC {

Matrix::Matrix(const std::vector<std::vector<float>>& input) {
    rows = input.size();
    cols = input[0].size();
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
    }
    for (int i = 0; i < rows; i++) {
        if (input.at(i).size() != cols) {
            printf("bad matrix v2\n");
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            data[i][j] = input[i][j];
        }
    }
}

Matrix::Matrix(int a, int b) {
    if (a < 1 or b < 1) {
        printf("bad matrix\n");
        exit(1);
    }
    rows = a;
    cols = b;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
    }
}

Matrix::Matrix(int n) {
    rows = n;
    cols = n;

    data = new float*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new float[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = ((i - j) == 0);
        }
    }
}

Matrix::Matrix() {
    rows = 1;
    cols = 1;

    data = new float*;
    data[0] = new float;
    data[0][0] = 1;
}

Matrix::Matrix(const Matrix& m) {
    rows = m.getRows();
    cols = m.getCols();

    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete data[i];
    }
    delete data;
}

bool Matrix::operator==(const Matrix& rhs) const {
    if (rows != rhs.rows || cols != rhs.cols) {
        return 0;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!roughlyEquals(data[i][j], rhs.data[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (cols != rhs.rows) {
        printf("bad multiplication\n");
    }
    auto result = Matrix(rows, rhs.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rhs.cols; j++) {
            // O(N^3) :'C
            float line = 0;
            for (int k = 0; k < rows; k++) {
                line += data[i][k] * rhs.data[k][j];
            }
            result.data[i][j] = line;
        }
    }
    return result;
}

Tuple Matrix::operator*(const Tuple& rhs) const {
    if (cols != 4 or rows != 4) {
        printf("bad multiplication by tuple\n");
    }
    std::vector<float> vResult = {};
    for (int i = 0; i < 4; i++) {
        float line = rhs.x * data[i][0] + rhs.y * data[i][1] +
                     rhs.z * data[i][2] + rhs.w * data[i][3];
        vResult.push_back(line);
    }
    return Tuple(vResult[0], vResult[1], vResult[2], vResult[3]);
}

Matrix Matrix::operator*(const float& scalar) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& rhs) {
    for (int i = 0; i < rhs.rows; i++) {
        std::string line = "";
        for (int j = 0; j < rhs.cols; j++) {
            line.append(" | ");
            line.append(std::to_string(rhs.data[i][j]));
        }
        line.append(" | \n");
        os << line;
        line = "";
    }
    return os;
}

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

float Matrix::determinant() const {
    if (rows != cols) {
        printf("bad determinant\n");
        exit(1);
    }
    if (rows == 1) {
        return data[0][0];
    }
    if (rows == 2) {
        return data[0][0] * data[1][1] - data[1][0] * data[0][1];
    } else {
        float result = 0;
        for (int i = 0; i < rows; i++) {
            result += data[0][i] * cofactor(0, i);
        }
        return result;
    }
}

float Matrix::minor(int i, int j) const {
    return submatrix(i, j).determinant();
}

float Matrix::cofactor(int i, int j) const {
    int sign = (i - j) % 2 ? -1 : 1;
    return minor(i, j) * sign;
}

bool Matrix::isInvertible() const { return determinant() != 0; }

Matrix Matrix::submatrix(int row, int col) const {
    if (row < 0 || row > rows - 1 || col < 0 || col > cols - 1) {
        printf("bad indexes\n");
        exit(1);
    }
    if (rows == 1 or cols == 1) {
        printf("matrix is too small\n");
        exit(1);
    }
    auto result = Matrix(rows - 1, cols - 1);
    int k = -1, l;
    for (int i = 0; i < rows - 1; i++) {
        i == row ? k += 2 : k++;
        l = -1;
        for (int j = 0; j < cols - 1; j++) {
            j == col ? l += 2 : l++;
            result.data[i][j] = data[k][l];
        }
    }
    return result;
}

Matrix Matrix::inverse() const {
    if (!isInvertible()) {
        printf("non invertible matrix\n");
        exit(1);
    }
    float det = determinant();
    Matrix cofactorMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cofactorMatrix.data[i][j] = cofactor(i, j) / det;
        }
    }
    return cofactorMatrix.transpose();
}

Matrix Matrix::transpose() {
    auto result = Matrix(cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

}  // namespace RTC