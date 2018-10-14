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
	cout << "1.ͬά�������ļӷ�" << endl
		<< "2.ͬά�������ļ���" << endl
		<< "3.һԪ����ʽ�ļӷ�" << endl
		<< "4.һԪ����ʽ�ļ���" << endl
		<< "5.�����ļн�����ֵ" << endl
		<< "6.���׵���" << endl
		<< "7.����ʽ�ĳ˷�" << endl
		<< "��ѡ��һ������" << endl;
}

void Operate::FunctionBox(int c)
{
	switch (c)
	{
	case 1: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�������һ������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "������ڶ�������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Add(v2);
		cout << "��������: ";
		v1.print();
		break;
	}
	case 2: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�����뱻������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "�������������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Minus(v2);
		cout << "��������: ";
		v1.print();
		break;
	}
	case 3: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "��ָ����С,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "��ָ����С,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.add(l2);
		s1.Add(s2);
		cout << "�����������:";
		l1.print();
		cout << "˳����������:";
		s1.print();
		break;
	}
	case 4: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "�ڶ�������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.minus(l2);
		s1.Minus(s2);
		cout << "�����������:";
		l1.print();
		cout << "˳����������:";
		s1.print();
		break;
	}
	case 5: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�������һ������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "������ڶ�������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);

		cout << "�������нǵ�����ֵΪ:" << v1.getCosAngle(v2) << endl;

		break;
	}
	case 6: {
		int d;
		int num;
		List l;
		cout << "������ԭʼ����ʽ������:" << endl;
		cin >> d;
		for (int i = 0; i < d; i++) {
			double coef;
			int expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l.addNode(ListNode(coef, expn));
		}
		l.print();
		cout << "�������󵼴���:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			l.Derivation();
		}
		cout << "�󵼽����:";
		l.print();
		break;
	}
	case 7: {
		int d1, d2;
		List l1, l2, result;
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			int coef, expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l1.addNode(ListNode(coef, expn));
		}
		l1.print();
		cout << "�ڶ�������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			int coef, expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l2.addNode(ListNode(coef, expn));
		}
		l2.print();
		l1.multiply(l2, result);
		cout << "��������:";
		result.print();
		break;
	}
	default:
		break;
	}
}
