#pragma once
#include "Arithmetic.h"
class ArithmeticX
{
public:
	ArithmeticX();
	ArithmeticX(string exp,string vn);//���캯��
	ArithmeticX(const ArithmeticX & ax);//���ƹ��캯��
	Arithmetic Assign(double val);//��ֵ����
	void print();
	~ArithmeticX();
private:
	string VariableName;//������
	string Expression;//���ʽ
	string AssignedExpression;//��ֵ����ʽ
};

