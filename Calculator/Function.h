#pragma once
#include "ArithmeticX.h"
#include <list>
class Function
{
public:
	Function();
	Function(string exp, string vn, string fn);
	Function(const Function & func);//复制构造函数
	void print();//输出函数
	static Function * DEF(const string & input,std::list<Function * > & func);//静态DEF函数，用于生成Function实例,并返回其指针
	void RUN(double val);
	const string & getName() {
		return FuncName;
	}
	~Function();
private:
	ArithmeticX * ariX;//函数表达式
	string FuncName;//函数名
};

