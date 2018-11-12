#pragma once
class Matrix
{
public:
	Matrix();
	Matrix(int mat[][100], int row, int col);
	Matrix(const Matrix & mat);
	void add(const Matrix & mat);//����ӷ�
	void minus(const Matrix & mat);//�������
	void multiply(const Matrix & mat);//����˷�
	void Transpose();//ת��
	double CalcEigenvalue();//��������ֵ
	double CalcDeterminant();//��������ʽ��ֵ
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
	int data[100][100];
};

