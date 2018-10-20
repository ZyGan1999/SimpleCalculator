#pragma once
#include <stdlib.h>
#include <string>
#include <stack>
using namespace std;
class Arithmetic
{
public:
	Arithmetic();
	Arithmetic(string InfixExp);
	Arithmetic(string PostfixExp, int);
	Arithmetic(Arithmetic & ari);
	double getResult();
	~Arithmetic();
private:
	string InfixExpression;//��׺���ʽ
	string PostfixExpression;//��׺���ʽ
	bool isNumber(char c) {
		if (c >= '0'&&c <= '9') return true;
		else return false;
	}
	bool isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/';
	}
	double String2Num(string s);//�ַ���ת����
	void Calc(char op, stack<double> & s);
};

