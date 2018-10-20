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
	string InfixExpression;//中缀表达式
	string PostfixExpression;//后缀表达式
	bool isNumber(char c) {
		if (c >= '0'&&c <= '9') return true;
		else return false;
	}
	bool isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/';
	}
	double String2Num(string s);//字符串转数字
	void Calc(char op, stack<double> & s);
};

