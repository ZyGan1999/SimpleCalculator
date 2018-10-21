#pragma once
#include <stdlib.h>
#include <string>
#include <stack>
#include <map>
#include <iostream>
using namespace std;
class Arithmetic
{
public:
	Arithmetic();
	Arithmetic(string InfixExp);
	Arithmetic(string PostfixExp, int);
	Arithmetic(const Arithmetic & ari);
	void print();
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
	void Infix2Postfix();
	static map<char, int> opLevel;
};

