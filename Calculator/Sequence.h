#pragma once
#include "ListNode.h"
#include <iostream>
using namespace std;
class Sequence
{
public:
	Sequence();
	~Sequence();
	void Insert(int i, ListNode e);//��˳�����Ա�ĵ�i��λ��֮ǰ�����µ�Ԫ��e
	ListNode Delete(int i);//ɾ����i��Ԫ�ز�������
	int LocateElem(ListNode e, bool(*compare)(ListNode, ListNode));//���ҵ�һ��ֵ��e����compare()��Ԫ�ص�λ��
	void Add(Sequence s);//����ʽ�ļӷ�
	void Minus(Sequence s);//����ʽ�ļ���
	void print();//�����ǰ����ʽ
protected:
	ListNode * _elem;
	int length;//���ȣ���ʼ��Ϊ0
	int listsize;//��ǰ����Ĵ洢����
};

