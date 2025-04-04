#include "matrix.hpp"
#include <stdexcept>
using namespace std;

// creates a matrix nxn
Matrix::Matrix(size_t N) : size(N) {
    // initialize matrix to 0
    data.resize(N, vector<int>(N, 0));
}
// create matrix from data
Matrix::Matrix(const vector<vector<int>>& num) {
    size = num.size();
    data = num;
}
// addition operator 
Matrix Matrix::operator+(const Matrix &rhs) const {
    // check size
    if (size != rhs.size) {
        throw invalid_argument("Error: Matrix sizes do not match (addition).");
    }
    // make result
    Matrix result(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            // add result
            result.data[i][j] = data[i][j] + rhs.data[i][j];
        }
    }
    return result;
}
// multiplication operator
Matrix Matrix::operator*(const Matrix &rhs) const {
    // check size
    if (size != rhs.size) {
        throw invalid_argument("Error: Matrix sizes do not match (multiplication).");
    }
    // make result
    Matrix result(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                // multiply result
                result.data[i][j] += data[i][k] * rhs.data[k][j];
            }
        }
    }
    return result;
}
// set specific position
void Matrix::set_value(size_t i, size_t j, int n) {
    if (i >= size || j >= size) {
        throw out_of_range("Error: Indicies out of range.");
    }
    // new value
    data[i][j] = n;
}
// get specific position
int Matrix::get_value(size_t i, size_t j) const {
    if (i >= size || j >= size) {
        throw out_of_range("Error: Indicies out of range.");
    }
    // return value
    return data[i][j];
}
// get size
size_t Matrix::get_size() const {
    return size;
}
// diagonal elements sum
int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (size_t i =0; i < size; ++i) {
        // when row == column, add elements together 
        sum += data[i][size - 1 - i];
    }
    return sum;
}
// secondary diagonal elements
int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        // add from opposite diagonal 
        sum += data[i][size - 1 - i];
    }
    return sum;
}
// swap rows
void Matrix::swap_rows(size_t r1, size_t r2) {
    if (r1 >= size || r2 >= size) {
        throw out_of_range("Error: Row indicies out of range.");
    }
    swap(data[r1], data[r2]);
}
// swap columns
void Matrix::swap_cols(size_t c1, size_t c2) {
    if (c1 >= size || c2 >= size) {
        throw out_of_range("Error: Column indicies out of range.");
    }
    for (size_t i = 0; i < size; ++i) {
        swap(data[i][c1], data[i][c2]);
    }
}
// print matrix
void Matrix::print_matrix() const {
    for (const auto& row : data) {
        for (int num : row) {
            cout << setw(2) << setfill('0') << num << " ";
        }
        cout << endl;
    }
}
