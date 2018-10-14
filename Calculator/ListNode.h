#pragma once
class ListNode
{
public:
	ListNode();
	ListNode(const ListNode &node);
	ListNode(double coef, int expn);
	~ListNode();
	double _coef;//系数
	int _expn;//指数
	ListNode * _next;
	ListNode * _prev;
	bool operator ==(const ListNode & node)const {
		if (this->_coef == node._coef&&this->_expn == node._expn) return true;
		return false;
	}
	ListNode operator -()const {
		ListNode ret(-_coef, _expn);
		return ret;
	}
};

