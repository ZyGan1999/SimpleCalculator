#pragma once
class ListNode
{
public:
	ListNode();//默认构造函数
	ListNode(const ListNode &node);//复制构造函数
	ListNode(double coef, int expn);//构造函数
	~ListNode();
	double _coef;//系数
	int _expn;//指数
	ListNode * _next;//下一节点指针，方便在链表中使用
	ListNode * _prev;//上一结点指针，方便在链表中使用
	bool operator ==(const ListNode & node)const {
		if (this->_coef == node._coef&&this->_expn == node._expn) return true;
		return false;
	}
	ListNode operator -()const {//负号重载
		ListNode ret(-_coef, _expn);
		return ret;
	}
};

