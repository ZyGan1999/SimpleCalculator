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
	Arithmetic(string InfixExp);//构造函数
	Arithmetic(string PostfixExp, int);
	Arithmetic(const Arithmetic & ari);//复制构造函数
	void print();
	static double String2Num(string s);//字符串转数字
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
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
	}
	
	void Calc(char op, stack<double> & s);
	void Infix2Postfix();//前缀表达式转后缀表达式
	static map<char, int> opLevel;//运算符的等级
};

