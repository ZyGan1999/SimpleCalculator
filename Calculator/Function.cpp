#include "Function.h"


Function::Function()
{
	ariX = nullptr;
	FuncName = "";
}

Function::Function(string exp, string vn, string fn)
{
	ariX = new ArithmeticX(exp, vn);
	FuncName = fn;
}

Function::Function(const Function & func)
{
	this->ariX = func.ariX;
	this->FuncName = func.FuncName;
}

void Function::print()
{
	cout << FuncName << "( " << ariX->getVarName() << " ) = ";
	ariX->print();
}

Function * Function::DEF(const string & input)
{
	int le = input.length();
	int curPos = 0;
	string fn = "";
	string vn = "";
	string exp = "";
	for (; input[curPos] != '('; ++curPos) {
		fn += input[curPos];
	}
	for (++curPos; input[curPos] != ')'; ++curPos) {
		vn += input[curPos];
	}
	for (curPos += 2; curPos < le; ++curPos) {
		exp += input[curPos];
	}
	auto ret = new Function(exp, vn, fn);
	return ret;
}

void Function::RUN(double val)
{
	auto ari = this->ariX->Assign(val);
	cout << ari.getResult() << endl;
}


Function::~Function()
{
	delete ariX;
}
