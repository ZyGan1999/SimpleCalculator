#include "Operate.h"
#include <iostream>
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
	default:
		break;
	}
}
