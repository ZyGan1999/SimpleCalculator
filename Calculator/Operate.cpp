#include "Operate.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

Operate::Operate()
{
}


Operate::~Operate()
{
}

void Operate::printMenu()
{
	cout << "1.同维度向量的加法" << endl
		<< "2.同维度向量的减法" << endl
		<< "3.一元多项式的加法" << endl
		<< "4.一元多项式的减法" << endl
		<< "5.向量的夹角余弦值" << endl
		<< "6.求多阶导数" << endl
		<< "7.多项式的乘法" << endl
		<< "8.四则运算表达式求值" << endl
		<< "9.含未知数的表达式求值" << endl
		<< "10.操作自定义函数" << endl
		<< "请选择一个操作" << endl;
}

void Operate::FunctionBox(int c)
{
	switch (c)
	{
	case 1: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入第一个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入第二个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Add(v2);
		cout << "运算结果是: ";
		v1.print();
		break;
	}
	case 2: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入被减向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入减数向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Minus(v2);
		cout << "运算结果是: ";
		v1.print();
		break;
	}
	case 3: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "按指数大小,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "第一个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "按指数大小,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.add(l2);
		s1.Add(s2);
		cout << "链表计算结果是:";
		l1.print();
		cout << "顺序表计算结果是:";
		s1.print();
		break;
	}
	case 4: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "第二个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.minus(l2);
		s1.Minus(s2);
		cout << "链表计算结果是:";
		l1.print();
		cout << "顺序表计算结果是:";
		s1.print();
		break;
	}
	case 5: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入第一个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入第二个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);

		cout << "两向量夹角的余弦值为:" << v1.getCosAngle(v2) << endl;

		break;
	}
	case 6: {
		int d;
		int num;
		List l;
		cout << "请输入原始多项式的项数:" << endl;
		cin >> d;
		for (int i = 0; i < d; i++) {
			double coef;
			int expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l.addNode(ListNode(coef, expn));
		}
		l.print();
		cout << "请输入求导次数:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			l.Derivation();
		}
		cout << "求导结果是:";
		l.print();
		break;
	}
	case 7: {
		int d1, d2;
		List l1, l2, result;
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			int coef, expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l1.addNode(ListNode(coef, expn));
		}
		l1.print();
		cout << "第二个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			int coef, expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l2.addNode(ListNode(coef, expn));
		}
		l2.print();
		l1.multiply(l2, result);
		cout << "计算结果是:";
		result.print();
		break;
	}
	case 8: {
		string exp;
		cout << "请输入四则运算表达式" << endl;
		cin >> exp;
		Arithmetic ari(exp);
		cout << "运算结果是: " << ari.getResult() << endl;
		break;
	}
	case 9: {
		string exp;
		string VarName;
		double Val;
		cout << "请输入变量名" << endl;
		cin >> VarName;
		cout << "请输入表达式" << endl;
		cin >> exp;
		cout << "请输入变量的值" << endl;
		cin >> Val;
		ArithmeticX ariX(exp, VarName);
		auto ari = ariX.Assign(Val);
		cout << "运算结果是: " << ari.getResult() << endl;
		break;
	}
	case 10: {
		cout << "可以开始输入指令了" << endl;
		string instruction = "";
		getline(cin, instruction);
		getline(cin, instruction);
		std::list<Function * > funcs;
		
		while (instruction != "ESC") {
			string insName = instruction.substr(0, 3);
			string input = "";
			try{input = instruction.substr(4, instruction.length() - 4);}
			catch (const exception& e) { ; }
			if (insName == "DEF") {
				auto f = Function::DEF(input,funcs);
				funcs.push_back(f);
			}
			else if (insName == "RUN") {
				string funcName = "";
				string Val_str = "";
				int curPos = 0;
				while (input[curPos] != '(') {
					funcName += input[curPos];
					++curPos;
				}
				++curPos;
				while (input[curPos] != ')') {
					Val_str += input[curPos];
					++curPos;
				}
				double val = Arithmetic::String2Num(Val_str);
				for (auto it = funcs.begin(); it != funcs.end(); ++it) {
					if ((*it)->getName() == funcName) {
						cout << "结果是: ";
						(*it)->RUN(val);
						break;
					}
					if (it == funcs.end()) cout << "没有找到对应函数" << endl;
				}
			}
			else if (insName == "WHO") {
				for (auto i : funcs) {
					//cout << (*i).getName() << ' ';
					i->print();
				}
				//cout << endl;
			}
			else {
				cout << "没有对应指令" << endl;
			}

			getline(cin, instruction);
		}
		break;
	}
	default:
		break;
	}
}

void Operate::test(int c)
{
	int dim = 11;//维数
	int x1[100] = { 2, -45, 32, -245, 0, 3442, 5, 0, 25, 56, -23 };//向量1
	int x2[100] = { 8, 90, 55, -3, 0, 67, 790, 234, 804, 0, -687 };//向量2
	Vector v1(11, x1);
	Vector v2(11, x2);

	List L1, L2;
	L1.add(5, 1000); L1.add(-1, 828); L1.add(7, 7); L1.add(-89, 5); L1.add(-23, 3); L1.add(90, 2); L1.add(-235, 1); L1.add(754, 0);
	L2.add(-34, 643); L2.add(554, 103); L2.add(-7, 7); L2.add(-89, 5); L2.add(243, 4); L2.add(-222, 2); L2.add(1, 0);
	//v1.print(); v2.print(); L1.print(); L2.print();
	switch (c)
	{
	case 1: {
		v1.Add(v2);
		v1.print();
		break;
	}
	case 2: {
		v1.Minus(v2);
		v1.print();
		break;
	}
	case 3: {
		L1.add(L2);
		L1.print();
		break;
	}
	case 4: {
		L1.minus(L2);
		L1.print();
		break;
	}
	case 5: {
		cout << v1.getCosAngle(v2) << endl;
		break;
	}
	case 6: {
		int num;
		cout << "请输入求导次数:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			L1.Derivation();
		}
		L1.print();
		break;
	}
	case 7: {
		List result;
		L1.multiply(L2, result);
		result.print();
		break;
	}
	default:
		break;
	}
}
