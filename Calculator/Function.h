#pragma once
#include "ArithmeticX.h"
class Function
{
public:
	Function();
	Function(string exp, string vn, string fn);
	Function(const Function & func);//���ƹ��캯��
	void print();//�������
	static Function * DEF(const string & input);//��̬DEF��������������Functionʵ��,��������ָ��
	void RUN(double val);
	const string & getName() {
		return FuncName;
	}
	~Function();
private:
	ArithmeticX * ariX;//�������ʽ
	string FuncName;//������
};

