#include "Arithmetic.h"



Arithmetic::Arithmetic()
{
}

Arithmetic::Arithmetic(string InfixExp)
{
	this->InfixExpression = InfixExp;
	this->PostfixExpression = "";
}

Arithmetic::Arithmetic(string PostfixExp, int)
{
	this->InfixExpression = "";
	this->PostfixExpression = PostfixExp;
}

Arithmetic::Arithmetic(Arithmetic & ari)
{
	this->InfixExpression = ari.InfixExpression;
	this->PostfixExpression = ari.PostfixExpression;
}

double Arithmetic::getResult()
{
	stack<double> tmp;
	for (int i = 0; i < PostfixExpression.length(); i++) {
		if (isOperator(PostfixExpression[i])) Calc(PostfixExpression[i], tmp);
		else if(isNumber(PostfixExpression[i])) {
			string curNum_Str = "";
			int j = i;
			while ((isNumber(PostfixExpression[j]) || PostfixExpression[j] == '.')&&j < PostfixExpression.length()&& PostfixExpression[j] != ' ') {
				curNum_Str += PostfixExpression[j];
				j++;
			}
			i = j;
			tmp.push(String2Num(curNum_Str));
		}
	}
	return tmp.top();
}


Arithmetic::~Arithmetic()
{
}

double Arithmetic::String2Num(string s)
{
	double ret = 0.0;
	int PointPosition = s.length();
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != '.') {
			ret *= 10;
			ret += (s[i] - '0');
		}
		else PointPosition = i + 1;
	}
	for (; PointPosition < s.length(); PointPosition++) ret /= 10;
	return ret;
}

void Arithmetic::Calc(char op, stack<double>& s)
{
	double ret;
	if (s.size() < 2) return;
	double Val2 = s.top();
	s.pop();
	double Val1 = s.top();
	s.pop();
	switch (op)
	{
	case '+': {
		ret = Val1 + Val2;
		break;
	}
	case '-': {
		ret = Val1 - Val2;
		break;
	}
	case '*': {
		ret = Val1 * Val2;
		break;
	}
	case '/': {
		ret = Val1 / Val2;
		break;
	}
	default:
		break;
	}
	s.push(ret);
}
