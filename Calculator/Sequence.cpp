#include "Sequence.h"
#include <stdlib.h>
#define LIST_INIT_SIZE 100//存储空间的初始分配量
#define LISTINCREMENTAL 10//存储空间的分配增量
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
	if (length >= listsize) {//当前存储空间已满，增加分配
		ListNode * newbase = (ListNode *)realloc(_elem, (listsize + LISTINCREMENTAL) * sizeof(ListNode));
		if (!newbase) exit(0);
		_elem = newbase;
		listsize += LISTINCREMENTAL;
	}
	ListNode * q = &_elem[i - 1];//插入位置
	for (ListNode * p = &_elem[length - 1]; p >= q; --p) {
		//插入位置及之后的元素右移
		*(p + 1) = *p;
	}
	*q = e;
	length++;
}

ListNode Sequence::Delete(int i)
{
	if (i<1 || i>length)exit(0);
	ListNode * p = &_elem[i - 1];//被删除元素的位置
	ListNode ret = *p;
	ListNode * q = _elem + length - 1;//表尾元素的位置
	for (++p; p <= q; ++p) {
		//被删除元素之后的元素左移
		*(p - 1) = *p;
	}
	length--;
	return ret;
}

int Sequence::LocateElem(ListNode e, bool(*compare)(ListNode, ListNode))
{//查找第一个值与e满足compare()的元素的位序,否则返回0
	int i = 1;
	ListNode * p = _elem;
	while (i <= length && !(*compare)(*p++, e)) ++i;
	if (i <= length) return i;
	else return 0;
}

void Sequence::Add(Sequence s)
{
	//将另一个顺序表多项式到其上
	//默认所有多项式的每一项的指数是单调递增的
	ListNode * pa = this->_elem;//用于遍历用作被加数的顺序表
	ListNode * pb = s._elem;//用于遍历用作加数的顺序表
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
	//减去另一个多项式
	//默认所有多项式的每一项的指数是单调递增的
	ListNode * pa = this->_elem;//用于遍历用作被减数的顺序表
	ListNode * pb = s._elem;//用于遍历用作减数的顺序表
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
