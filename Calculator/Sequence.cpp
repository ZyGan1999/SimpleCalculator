#include "Sequence.h"
#include <stdlib.h>
#define LIST_INIT_SIZE 100//�洢�ռ�ĳ�ʼ������
#define LISTINCREMENTAL 10//�洢�ռ�ķ�������
Sequence::Sequence()
{
	this->_elem = (ListNode * )malloc(LIST_INIT_SIZE * sizeof(ListNode));
	length = 0;
	listsize = LIST_INIT_SIZE;
}


Sequence::~Sequence()
{
	/*if (_elem != nullptr) delete _elem;*/
}

void Sequence::Insert(int i, ListNode e)
{
	if (i<1 || i>length + 1) exit(1);
	if (length >= listsize) {//��ǰ�洢�ռ����������ӷ���
		ListNode * newbase = (ListNode *)realloc(_elem, (listsize + LISTINCREMENTAL) * sizeof(ListNode));
		if (!newbase) exit(0);
		_elem = newbase;
		listsize += LISTINCREMENTAL;
	}
	ListNode * q = &_elem[i - 1];//����λ��
	for (ListNode * p = &_elem[length - 1]; p >= q; --p) {
		//����λ�ü�֮���Ԫ������
		*(p + 1) = *p;
	}
	*q = e;
	length++;
}

ListNode Sequence::Delete(int i)
{
	if (i<1 || i>length)exit(0);
	ListNode * p = &_elem[i - 1];//��ɾ��Ԫ�ص�λ��
	ListNode ret = *p;
	ListNode * q = _elem + length - 1;//��βԪ�ص�λ��
	for (++p; p <= q; ++p) {
		//��ɾ��Ԫ��֮���Ԫ������
		*(p - 1) = *p;
	}
	length--;
	return ret;
}

int Sequence::LocateElem(ListNode e, bool(*compare)(ListNode, ListNode))
{//���ҵ�һ��ֵ��e����compare()��Ԫ�ص�λ��,���򷵻�0
	int i = 1;
	ListNode * p = _elem;
	while (i <= length && !(*compare)(*p++, e)) ++i;
	if (i <= length) return i;
	else return 0;
}

void Sequence::Add(Sequence s)
{
	//����һ��˳������ʽ������
	//Ĭ�����ж���ʽ��ÿһ���ָ���ǵ���������
	ListNode * pa = this->_elem;//���ڱ���������������˳���
	ListNode * pb = s._elem;//���ڱ�������������˳���
	for (int i = 0; i < s.length; i++) {
		pa = this->_elem;
		int paAddNum = 0;
		while (pb->_expn > pa->_expn && paAddNum < length) {
			pa++;
			paAddNum++;
		}
		if (pa->_expn == pb->_expn) { 
			pa->_coef += pb->_coef;
			if (pa->_coef == 0) Delete(paAddNum + 1);
		}
		else Insert(paAddNum + 1, *pb);
		pb++;
	}
}

void Sequence::Minus(Sequence s)
{
	//��ȥ��һ������ʽ
	//Ĭ�����ж���ʽ��ÿһ���ָ���ǵ���������
	ListNode * pa = this->_elem;//���ڱ���������������˳���
	ListNode * pb = s._elem;//���ڱ�������������˳���
	for (int i = 0; i < s.length; i++) {
		pa = this->_elem;
		int paAddNum = 0;
		while (pb->_expn > pa->_expn && paAddNum < length) {
			pa++;
			paAddNum++;
		}
		if (pa->_expn == pb->_expn) {
			pa->_coef -= pb->_coef;
			if (pa->_coef == 0) Delete(paAddNum + 1);
		}
		else Insert(paAddNum + 1, -(*pb));
		pb++;
	}
}

void Sequence::print()
{
	ListNode * p = _elem + length - 1;
	bool flag = true;
	while (p >= _elem) {
		if (flag) {
			flag = false;
			cout << p->_coef << "*x" << '^' << p->_expn;
		}
		else {
			if (p->_coef > 0) {
				cout << "+" << p->_coef << "*x" << '^' << p->_expn;
			}
			else cout << p->_coef << "*x" << '^' << p->_expn;
		}
		p--;
	}
	cout << endl;
}
