#ifndef SPARSEMATRIX_CPP
#define SPARSEMATRIX_CPP

#include "sparsematrix.h"
#include <iomanip>

template <typename T>
SparseMatrix<T>::SparseMatrix()
{
    pointers.push_back(0);
    this->precision = 1;
    this->width = 1;
    this->n = 0;
}

template <typename T>
SparseMatrix<T>::SparseMatrix(unsigned int m, unsigned int n, int precision, int width)
{
    this->precision = precision;
    this->width = width;
    this->n = n;
    pointers.assign(m + 1, 0);
}

template <typename T>
void SparseMatrix<T>::setVal(T val, unsigned int row, unsigned int col)
{
    if (n < col + 1) {
        n = col + 1;
    }
    int pos = -1;
    if (row >= pointers.size() - 1) {
        pos = pointers.back();
        for (unsigned int i = pointers.size() - 1; i <= row; i++) {
            pointers.push_back(pos);
        }
    } else if (pointers[row] == pointers[row + 1]) {
        pos = pointers[row];
    } else {
        for (unsigned int k = pointers[row]; pos == -1; k++) {
            if (k == pointers[row + 1] || cols[k] >= col) {
                pos = k;
            }
        }
    }
    if (pointers[row] != pointers[row + 1] && pos < int(cols.size()) && cols[pos] == col) {
        if (val) {
            values[pos] = val;
        } else {
            delVal(row, pos);
        }
    } else if (val) {
        values.insert(values.begin() + pos, val);
        cols.insert(cols.begin() + pos, col);
        for (unsigned int i = row + 1; i < pointers.size(); i++) {
            pointers[i]++;
        }
    }
}

template <typename T>
T SparseMatrix<T>::getVal(unsigned int row, unsigned int col)
{
    if (row < numRows() && col < n) {
        for (unsigned int i = pointers[row]; cols[i] <= col && i < pointers[row + 1]; i++) {
            if (cols[i] == col) {
                return values[i];
            }
        }
    }
    return 0;
}

template <typename T>
bool SparseMatrix<T>::delRow(unsigned int row)
{
    if (row < numRows()) {
        unsigned int n = pointers[row + 1];
        if (n > pointers[row]) {
            values.erase(values.begin() + pointers[row], values.begin() + n);
            cols.erase(cols.begin() + pointers[row], cols.begin() + n);
            n -= pointers[row];
            for (unsigned int i = row + 1; i < pointers.size(); i++) {
                pointers[i] -= n;
            }
        }
        pointers.erase(pointers.begin() + row);
        return true;
    }
    return false;
}

template <typename T>
bool SparseMatrix<T>::delCol(unsigned int col)
{
    if (col < n) {
        n--;
        unsigned int i = 0, j = 0;
        while (j < cols.size()) {
            while (j == pointers[i + 1]) {
                i++;
            }
            if (cols[j] == col) {
                delVal(i, j);
            } else {
                if (cols[j] > col) {
                    cols[j]--;
                }
                j++;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
unsigned int SparseMatrix<T>::numRows()
{
    return pointers.size() - 1;
}

template <typename T>
unsigned int SparseMatrix<T>::numCols()
{
    return n;
}

template <typename T>
int SparseMatrix<T>::memUsed()
{
    return sizeof(values) + sizeof(T) * values.capacity() + sizeof(cols) + sizeof(pointers) + sizeof(int) * (cols.capacity() + pointers.capacity() + 2);
}

template <typename T>
void SparseMatrix<T>::delVal(unsigned int row, unsigned int pos)
{
    values.erase(values.begin() + pos);
    cols.erase(cols.begin() + pos);
    for (unsigned int i = row + 1; i < pointers.size(); i++) {
        pointers[i]--;
    }
}

template <typename T>
std::ostream& SparseMatrix<T>::matrixToOstream(std::ostream& os)
{
    unsigned int k = 0;
    for (unsigned int i = 1; i < pointers.size(); i++) {
        unsigned int j = 0;
        while (k < pointers[i]) {
            while (j < cols[k]) {
                os << std::setw(width) << 0 << ' ';
                j++;
            }
            os << std::setprecision(precision) << std::setw(width) << values[k++] << ' ';
            j++;
        }
        while (j < n) {
            os << std::setw(width) << 0 << ' ';
            j++;
        }
        os << std::endl;
    }
    return os;
}

template <typename U>
std::ostream& operator<< (std::ostream& os, SparseMatrix<U>& a)
{
    return a.matrixToOstream(os);
}

#endif //SPARSEMATRIX_CPP
