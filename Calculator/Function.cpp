#include "Function.h"
#include <list>

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

Function * Function::DEF(const string & input, std::list<Function * > & funcs)
{
	//扫描输入信息
	//拆分字符串，用于生成实例
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

	for (auto i : funcs) {
		while (exp.find(i->FuncName) != string::npos) {
			int pos = exp.find(i->FuncName);
			int num = 0;
			while (exp[num + pos] != ')') num++;
			auto CalledArix = new ArithmeticX(*(i->ariX));
			if(vn != CalledArix->VariableName) CalledArix->ChangeVarName(vn);
			string change = CalledArix->Expression;
			change = '(' + change + ')';
			exp.replace(pos, num + 1, change);
		}
	}

	auto ret = new Function(exp, vn, fn);
	ret->print();
	return ret;
}

void Function::RUN(double val)
{
	//赋值并运算
	auto ari = this->ariX->Assign(val);
	cout << ari.getResult() << endl;
}


Function::~Function()
{
	delete ariX;
}
