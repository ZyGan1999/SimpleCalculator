#include "Matrix.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
Matrix::Matrix()
{
	//data = (int**)malloc(100000 * sizeof(int));
	rowNum = 0;
	colNum = 0;
}

Matrix::Matrix(double mat[][100], int row, int col)
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

Matrix::Matrix(int row, int col)
{
	rowNum = row;
	colNum = col;
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < colNum; ++j) {
			data[i][j] = 0;
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

Matrix * Matrix::multiply(const Matrix & mat)
{
	auto rtn = new Matrix(this->rowNum, mat.colNum);
	for (int ci = 0; ci < rtn->rowNum; ci++) {
		for (int cj = 0; cj < rtn->colNum; cj++) {
			int result = 0;
			for (int pos = 0; pos < this->rowNum; pos++) {
				result += this->data[ci][pos] * mat.data[pos][cj];
			}
			rtn->data[ci][cj] = result;
		}
	}
	return rtn;
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
	double pdbEigenValues[100] = { 0 };
	double dbEps = 0.00001f;
	int nJt = 1000;
	auto pMatrix = new Matrix(this->data, rowNum, colNum);
	auto pdblVects = new Matrix(rowNum, colNum);
	//
	for (int i = 0; i < rowNum; i++)
	{
		pdblVects->data[i][i] = 1.0f;
		for (int j = 0; j < rowNum; j++)
		{
			if (i != j)
				pdblVects->data[i][j] = 0.0f;
		}
	}

	int nCount = 0;		//迭代次数
	while (1)
	{
		//在pMatrix的非对角线上找到最大元素
		double dbMax = pMatrix->data[0][1];
		int nRow = 0;
		int nCol = 1;
		for (int i = 0; i < rowNum; i++)			//行
		{
			for (int j = 0; j < rowNum; j++)		//列
			{
				double d = fabs(pMatrix->data[i][j]);

				if ((i != j) && (d> dbMax))
				{
					dbMax = d;
					nRow = i;
					nCol = j;
				}
			}
		}

		if (dbMax < dbEps)     //精度符合要求 
			break;

		//if (nCount > nJt)       //迭代次数超过限制
		//	break;

		nCount++;

		double dbApp = pMatrix->data[nRow][nRow];
		double dbApq = pMatrix->data[nRow][nCol];
		double dbAqq = pMatrix->data[nCol][nCol];

		//计算旋转角度
		double dbAngle = 0.5*atan2(-2 * dbApq, dbAqq - dbApp);
		double dbSinTheta = sin(dbAngle);
		double dbCosTheta = cos(dbAngle);
		double dbSin2Theta = sin(2 * dbAngle);
		double dbCos2Theta = cos(2 * dbAngle);

		pMatrix->data[nRow][nRow] = dbApp * dbCosTheta*dbCosTheta +
			dbAqq * dbSinTheta*dbSinTheta + 2 * dbApq*dbCosTheta*dbSinTheta;
		pMatrix->data[nCol][nCol] = dbApp * dbSinTheta*dbSinTheta +
			dbAqq * dbCosTheta*dbCosTheta - 2 * dbApq*dbCosTheta*dbSinTheta;
		pMatrix->data[nRow][nCol] = 0.5*(dbAqq - dbApp)*dbSin2Theta + dbApq * dbCos2Theta;
		pMatrix->data[nCol][nRow] = pMatrix->data[nRow][nCol];

		for (int i = 0; i < rowNum; i++)
		{
			if ((i != nCol) && (i != nRow))
			{
				//int u = i * nDim + nRow;	//p  
				//int w = i * nDim + nCol;	//q
				dbMax = pMatrix->data[i][nRow];
				pMatrix->data[i][nRow] = pMatrix->data[i][nCol] * dbSinTheta + dbMax * dbCosTheta;
				pMatrix->data[i][nCol] = pMatrix->data[i][nCol] * dbCosTheta - dbMax * dbSinTheta;
			}
		}

		for (int j = 0; j < rowNum; j++)
		{
			if ((j != nCol) && (j != nRow))
			{
				//int u = nRow * nDim + j;	//p
				//int w = nCol * nDim + j;	//q
				dbMax = pMatrix->data[nRow][j];
				pMatrix->data[nRow][j] = pMatrix->data[nCol][j] * dbSinTheta + dbMax * dbCosTheta;
				pMatrix->data[nCol][j] = pMatrix->data[nCol][j] * dbCosTheta - dbMax * dbSinTheta;
			}
		}

		//计算特征向量
		for (int i = 0; i < rowNum; i++)
		{
			//int u = i * nDim + nRow;		//p   
			//int w = i * nDim + nCol;		//q
			dbMax = pdblVects->data[i][nRow];
			pdblVects->data[i][nRow] = pdblVects->data[i][nCol] * dbSinTheta + dbMax * dbCosTheta;
			pdblVects->data[i][nCol] = pdblVects->data[i][nCol] * dbCosTheta - dbMax * dbSinTheta;
		}
		pMatrix->print();
	}

	//对特征值进行排序以及重新排列特征向量,特征值即pMatrix主对角线上的元素
	std::map<double, int> mapEigen;
	for (int i = 0; i < rowNum; i++)
	{
		pdbEigenValues[i] = pMatrix->data[i][i];

		mapEigen.insert(make_pair(pdbEigenValues[i], i));
	}

	double *pdbTmpVec = new double[rowNum*rowNum];
	std::map<double, int>::reverse_iterator iter = mapEigen.rbegin();
	for (int j = 0; iter != mapEigen.rend(), j < rowNum; ++iter, ++j)
	{
		for (int i = 0; i < rowNum; i++)
		{
			pdbTmpVec[i*rowNum + j] = pdblVects->data[i][iter->second];
		}

		//特征值重新排列
		pdbEigenValues[j] = iter->first;
	}

	//设定正负号
	for (int i = 0; i < rowNum; i++)
	{
		double dSumVec = 0;
		for (int j = 0; j < rowNum; j++)
			dSumVec += pdbTmpVec[j * rowNum + i];
		if (dSumVec<0)
		{
			for (int j = 0; j < rowNum; j++)
				pdbTmpVec[j * rowNum + i] *= -1;
		}
	}

	memcpy(pdblVects, pdbTmpVec, sizeof(double)*rowNum*rowNum);
	delete[]pdbTmpVec;
	for (auto i : mapEigen) {
		cout << ((i.first < dbEps) ? (0) : (i.first)) << ' ';
	}
	cout << endl;
	return 1;
}
double Matrix::CE()
{
	if (rowNum != colNum) return 0;

	for (int i = 0; i < rowNum; ++i) {
		for (int j = i; j < rowNum; ++j) {
			this->data[i][j] = this->data[j][i];
		}
	}

	Matrix tmp(rowNum, colNum);
	for (int i = 0; i < rowNum; ++i) {
		for (int j = 0; j < rowNum; ++j) {
			tmp.data[i][j] = this->data[i][j];
		}
	}

	cout << "转化后的矩阵为：" << endl;

	tmp.print();
	Matrix U(rowNum, rowNum);

	int num = 0;

	int p, q;
	double max;
	do {
		max = 0;
		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < rowNum; ++j) {
				if (i == j)continue;
				if (fabs(tmp.data[i][j]) > fabs(max)) {
					p = i;
					q = j;
					max = fabs(tmp.data[i][j]);
				}
			}
		}

		if (fabs(max) <= 0.01)break;

		//cout << max << endl;

		double tan2 = -2 * tmp.data[p][q] / (tmp.data[q][q] - tmp.data[p][p]);
		double Y = atan(tan2);
		double y = Y / 2;
		double sinY = sin(y), cosY = cos(y);

		//cout << "sss" << p << " " << q << endl;

		for (int i = 0; i < rowNum; ++i) {
			for (int j = 0; j < rowNum; ++j) {
				if (i == j) U.data[i][j] = 1;
				else U.data[i][j] = 0;
			}
		}

		U.data[p][p] = cosY;
		U.data[q][q] = cosY;
		U.data[p][q] = -sinY;
		U.data[q][p] = sinY;

		Matrix U0 = U;
		U.Transpose();
		tmp = *(U.multiply(tmp));
		tmp = *(tmp.multiply(U0));
		//tmp.print();
		//tmp = U.transpose() * tmp * U;

		++num;

	} while (fabs(max) > 0.01);
	cout << "迭代次数: " << num << endl;
	//cout << tmp << endl;
	int k = 0;
	vector<double> vc;
	for (int i = 0; i < rowNum; ++i)vc.push_back(tmp.data[i][i]);
	sort(vc.begin(), vc.end());
	cout << "特征值从小到大为：" << endl;
	for (auto k : vc) {
		//if (nearlyZero(k))k = 0;
		cout << k << endl;
	}
	cout << endl;
	return 1;
}
void Matrix::CE2()
{

}
	//


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
{}
