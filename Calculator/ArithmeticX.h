#pragma once
#include "Arithmetic.h"
class ArithmeticX
{
public:
	ArithmeticX();
	ArithmeticX(string exp,string vn);
	ArithmeticX(const ArithmeticX & ax);
	Arithmetic Assign(double val);
	void print();
	~ArithmeticX();
private:
	string VariableName;
	string Expression;
	string AssignedExpression;
};

