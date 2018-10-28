#include "Arithmetic.h"

map<char, int> Arithmetic::opLevel = {
	make_pair('#',-1),
	make_pair('(',0),
	make_pair('+',1),
	make_pair('-',1),
	make_pair('*',2),
	make_pair('/',2),
	make_pair('^',3)
};

Arithmetic::Arithmetic()
{
}

Arithmetic::Arithmetic(string InfixExp)
{
	this->InfixExpression = InfixExp;
	Infix2Postfix();
}

Arithmetic::Arithmetic(string PostfixExp, int)
{
	this->InfixExpression = "";
	this->PostfixExpression = PostfixExp;
}

Arithmetic::Arithmetic(const Arithmetic & ari)
{
	this->InfixExpression = ari.InfixExpression;
	this->PostfixExpression = ari.PostfixExpression;
}

void Arithmetic::print()
{
	//�������
	cout << "  Infix: " << InfixExpression << endl;
	cout << "Postfix: " << PostfixExpression << endl;
}

double Arithmetic::getResult()
{
	//��������������ʽ
	//ͨ����׺���ʽ
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
	//���ַ���ת��Ϊ����
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
	//��ջ�������������һ�ַ�������
	//�����ջ
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
	case '^': {
		ret = pow(Val1, Val2);
		break;
	}
	default:
		break;
	}
	s.push(ret);
}

void Arithmetic::Infix2Postfix()
{
	if (InfixExpression[0] == '-') {
		//������λ����
		InfixExpression = "0" + InfixExpression;
	}
	while (InfixExpression.find("(-") != string::npos) {
		//�����������
		int pos = InfixExpression.find("(-");
		InfixExpression.insert(pos + 1, 1, '0');
	}
	while (InfixExpression.find("*-") != string::npos) {
		//���������ֵ��Ĳ��Ϸ�����
		int pos = InfixExpression.find("*-");
		InfixExpression.insert(pos + 1, "(0");
		pos += 4;
		while (isNumber(InfixExpression[pos]) || InfixExpression[pos] == '.') pos++;
		InfixExpression.insert(pos, 1, ')');
	}
	while (InfixExpression.find("/-") != string::npos) {
		//���������ֵ��Ĳ��Ϸ�����
		int pos = InfixExpression.find("/-");
		InfixExpression.insert(pos + 1, "(0");
		pos += 4;
		while (isNumber(InfixExpression[pos]) || InfixExpression[pos] == '.') pos++;
		InfixExpression.insert(pos, 1, ')');
	}
	while (InfixExpression.find("^-") != string::npos) {
		//���������ֵ��Ĳ��Ϸ�����
		int pos = InfixExpression.find("^-");
		InfixExpression.insert(pos + 1, "(0");
		pos += 4;
		while (isNumber(InfixExpression[pos]) || InfixExpression[pos] == '.') pos++;
		InfixExpression.insert(pos, 1, ')');
	}
	stack<char> operators;
	operators.push('#');
	for (int i = 0; i < InfixExpression.length(); i++) {
		//ɨ�貢ת��
		if (InfixExpression[i] == '(') operators.push(InfixExpression[i]);
		else if (isNumber(InfixExpression[i])) {
			int j = i;
			string curNum = "";
			while ((isNumber(InfixExpression[j]) || InfixExpression[j] == '.')&& j < InfixExpression.length()) {
				curNum += InfixExpression[j];
				j++;
			}
			i = j - 1;
			PostfixExpression += curNum;
			PostfixExpression += " ";
		}
		else if (isOperator(InfixExpression[i])) {
			while (opLevel[InfixExpression[i]] <= opLevel[operators.top()]) {
				PostfixExpression += operators.top();
				PostfixExpression += " ";
				operators.pop();
			}
			operators.push(InfixExpression[i]);
		}
		else if (InfixExpression[i] == ')') {
			while (operators.top() != '(') {
				PostfixExpression += operators.top();
				PostfixExpression += " ";
				operators.pop();
			}
			operators.pop();
		}
	}
	while (operators.top() != '#') {
		PostfixExpression += operators.top();
		PostfixExpression += " ";
		operators.pop();
	}
}
