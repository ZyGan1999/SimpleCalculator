#pragma once
class Matrix
{
public:
	Matrix();
	Matrix(double mat[][100], int row, int col);
	Matrix(int row, int col);
	Matrix(const Matrix & mat);
	void add(const Matrix & mat);//矩阵加法
	void minus(const Matrix & mat);//矩阵减法
	Matrix * multiply(const Matrix & mat);//矩阵乘法
	void Transpose();//转置
	double CalcEigenvalue();//计算特征值
	double CE();
	void CE2();
	double CalcDeterminant();//计算行列式的值
	Matrix * getAij(int i, int j);
	void print();
	~Matrix();
	int getrowNum() {
		return rowNum;
	}
	int getcolNum() {
		return colNum;
	}
private:
	int rowNum;
	int colNum;
	double data[100][100];
};

