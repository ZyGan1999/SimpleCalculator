#include "ArithmeticX.h"



ArithmeticX::ArithmeticX()
{
}

ArithmeticX::ArithmeticX(string exp,string vn)
{
	this->Expression = exp;
	this->VariableName = vn;
	this->AssignedExpression = "";
}

ArithmeticX::ArithmeticX(const ArithmeticX & ax)
{
	this->AssignedExpression = ax.AssignedExpression;
	this->Expression = ax.Expression;
	this->VariableName = ax.VariableName;
}

Arithmetic ArithmeticX::Assign(double val)
{
	//赋值函数
	//通过给变量赋值，得到一个普通的四则运算表达式
	AssignedExpression = Expression;
	string Val_str = to_string(val);
	while (AssignedExpression.find(VariableName) != string::npos) {
		string former = "";
		string latter = "";
		int pos = AssignedExpression.find(VariableName);
		int i = 0;
		for (; i < pos; i++) {
			former += AssignedExpression[i];
		}
		for (i += VariableName.length(); i < AssignedExpression.length(); i++) {
			latter += AssignedExpression[i];
		}
		AssignedExpression = former + Val_str + latter;
	}
	Arithmetic ret(AssignedExpression);
	return ret;
}

void ArithmeticX::print()
{
	cout << Expression << endl;
	//cout << "AExp: " << AssignedExpression << endl;
}


ArithmeticX::~ArithmeticX()
{
}
