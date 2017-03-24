#ifndef ALGORITHM_MATRIX_H
#define ALGORITHM_MATRIX_H

#include <vector>
#include <stdexcept>

namespace myalgorithm {
    using std::vector;

    // 矩阵类
    template <typename T>
    class Matrix {
    public:
        Matrix(int rows=1, int cols=1, const T &initValue = T());

        void resize(int rows, int cols);

        vector<T>& operator[](int index);
        const vector<T>& operator[](int index) const;

        int rows() const { return _rows; }
        int cols() const { return _cols; }

        friend Matrix operator+(Matrix &lhs, Matrix &rhs);
        friend Matrix operator-(Matrix &lhs, Matrix &rhs);

    private:
        int _rows;
        int _cols;
        vector<vector<T>> matrix;
    };

    template <typename T>
    Matrix<T>::Matrix(int rows, int cols, const T &initValue) :
        _rows(rows), _cols(cols), matrix(rows, vector<T>(cols, initValue))
    {}

    template <typename T>
    void Matrix<T>::resize(int rows, int cols)
    {
        if (rows < 0 || cols < 0) {
            return;
        }

        if (rows == _rows && cols == _cols) {
            return;
        }

        _rows = rows;
        _cols = cols;
        matrix.resize(_rows);
        for (int i = 0; i < _rows; ++i) {
            matrix[i].resize(_cols);
        }
    }

    template <typename T>
    vector<T>& Matrix<T>::operator[](int index)
    {
        if (index < 0 || index >= _rows) {
            throw std::out_of_range("Matrix.[]: index out of range");
        }

        return matrix[index];
    }

    template <typename T>
    const vector<T>& Matrix<T>::operator[](int index) const
    {
        if (index < 0 || index >= _rows) {
            throw std::out_of_range("Matrix.[]: index out of range");
        }

        return matrix[index];
    }
    template <typename T>
    Matrix<T> operator+(Matrix<T> &lhs, Matrix<T> &rhs)
    {
        if ((lhs._rows == rhs._rows) && (lhs._cols == rhs._cols)) {
            Matrix<T> matrix(lhs);
            for (int row = 0; row < matrix._rows; ++row) {
                for (int col = 0; col < matrix._cols; ++col) {
                    matrix[row][col] += rhs[row][col];
                }
            }
            return matrix;
        } else {
            throw std::out_of_range("the rows and cols of both-hand side must be equal");
        }
    }

    template <typename T>
    Matrix<T> operator-(Matrix<T> &lhs, Matrix<T> &rhs)
    {
        if ((lhs._rows == rhs._rows) && (lhs._cols == rhs._cols)) {
            Matrix<T> matrix(lhs);
            for (int row = 0; row < matrix._rows; ++row) {
                for (int col = 0; col < matrix._cols; ++col) {
                    matrix[row][col] -= rhs[row][col];
                }
            }
            return matrix;
        } else {
            throw std::out_of_range("the rows and cols of both-hand side must be equal");
        }
    }
}

#endif  // ALGORITHM_MATRIX_H