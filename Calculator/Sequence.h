#pragma once
#include "ListNode.h"
#include <iostream>
using namespace std;
class Sequence
{
public:
	Sequence();
	~Sequence();
	void Insert(int i, ListNode e);//在顺序线性表的第i个位置之前插入新的元素e
	ListNode Delete(int i);//删除第i个元素并返回它
	int LocateElem(ListNode e, bool(*compare)(ListNode, ListNode));//查找第一个值与e满足compare()的元素的位序
	void Add(Sequence s);//多项式的加法
	void Minus(Sequence s);//多项式的减法
	void print();//输出当前多项式
protected:
	ListNode * _elem;
	int length;//长度，初始设为0
	int listsize;//当前分配的存储容量
};

