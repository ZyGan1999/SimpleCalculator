#include "Matrix.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
Matrix::Matrix()
{
	//data = (int**)malloc(100000 * sizeof(int));
	rowNum = 0;
	colNum = 0;
}

Matrix::Matrix(int mat[][100], int row, int col)
{
	//data = (int**)malloc(100000 * sizeof(int));
	rowNum = row;
	colNum = col;
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[i][j] = mat[i][j];
		}
	}
}

Matrix::Matrix(const Matrix & mat)
{
	//data = (int**)malloc(100000 * sizeof(int));
	rowNum = mat.rowNum;
	colNum = mat.colNum;
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[i][j] = mat.data[i][j];
		}
	}
}

void Matrix::add(const Matrix & mat)
{
	if (this->rowNum != mat.rowNum || this->colNum != mat.colNum) {
		cout << "Not Match" << endl;
		return;
	}
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[i][j] += mat.data[i][j];
		}
	}
}

void Matrix::minus(const Matrix & mat)
{
	if (this->rowNum != mat.rowNum || this->colNum != mat.colNum) {
		cout << "Not Match" << endl;
		return;
	}
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[i][j] -= mat.data[i][j];
		}
	}
}

void Matrix::multiply(const Matrix & mat)
{
}

void Matrix::Transpose()
{
	int olddata[100][100] = { {0} };
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			olddata[i][j] = data[i][j];
		}
	}

	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[j][i] = olddata[i][j];
		}
	}
	int tmp = rowNum;
	rowNum = colNum;
	colNum = tmp;
}

double Matrix::CalcEigenvalue()
{
	return 0.0;
}

double Matrix::CalcDeterminant()
{
	if (colNum == 1) return data[0][0];
	double rtn = 0;

	for (int j = 0; j < colNum; j++) {
		int sgn = (0 + j) % 2 ? (-1) : (1);
		rtn += data[0][j] * sgn * getAij(0, j)->CalcDeterminant();
	}
	return rtn;
}


Matrix * Matrix::getAij(int i, int j)
{
	//i,j >= 0
	auto rtn = new Matrix(data, rowNum, colNum);
	for (int pi = i; pi < rowNum - 1; pi++) {
		for (int pj = 0; pj < colNum; pj++) {
			rtn->data[pi][pj] = rtn->data[pi + 1][pj];
		}
	}
	for (int pj = j; pj < colNum - 1; pj++) {
		for (int pi = 0; pi < rowNum; pi++) {
			rtn->data[pi][pj] = rtn->data[pi][pj + 1];
		}
	}
	rtn->rowNum--;
	rtn->colNum--;
	return rtn;
}

void Matrix::print()
{
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "----------------------------------------" << endl;
}


Matrix::~Matrix()
{
	if (data != nullptr) delete data;
}
