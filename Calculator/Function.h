#pragma once
#include "ArithmeticX.h"
class Function
{
public:
	Function();
	Function(string exp, string vn, string fn);
	Function(const Function & func);
	void print();
	static Function * DEF(const string & input);
	void RUN(double val);
	const string & getName() {
		return FuncName;
	}
	~Function();
private:
	ArithmeticX * ariX;
	string FuncName;//º¯ÊýÃû
};

