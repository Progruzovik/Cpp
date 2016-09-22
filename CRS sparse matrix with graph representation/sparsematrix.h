#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <vector>

template <typename T>
class SparseMatrix
{
public:
	SparseMatrix();
	SparseMatrix(unsigned int n, unsigned int m, int precision, int width);
	int precision;
	int width;
	void setVal(T val, unsigned int row, unsigned int col);
	T getVal(unsigned int row, unsigned int col);
	bool delRow(unsigned int row);
	bool delCol(unsigned int col);
	unsigned int numRows();
	unsigned int numCols();
	int memUsed();
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, SparseMatrix<U> &a);

protected:
	unsigned int n;
	std::vector<T> values;
	std::vector<unsigned int> cols;
	std::vector<unsigned int> pointers;
	void delVal(unsigned int row, unsigned int pos);
    std::ostream &matrixToOstream(std::ostream &os);
};

#include "sparsematrix.cpp"

#endif //SPARSEMATRIX_H
