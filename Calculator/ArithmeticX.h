#pragma once
#include "Arithmetic.h"
class ArithmeticX
{
public:
	friend class Function;
	ArithmeticX();
	ArithmeticX(string exp,string vn);//构造函数
	ArithmeticX(const ArithmeticX & ax);//复制构造函数
	Arithmetic Assign(double val);//赋值函数
	void print();
	const string & getVarName() {
		return VariableName;
	}
	~ArithmeticX();
private:
	string VariableName;//变量名
	string Expression;//表达式
	string AssignedExpression;//赋值后表达式
};

