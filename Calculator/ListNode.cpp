#include "ListNode.h"



ListNode::ListNode()
{
}

ListNode::ListNode(const ListNode &node)
{
	_coef = node._coef;
	_expn = node._expn;
}

ListNode::ListNode(double coef, int expn)
{
	this->_coef = coef;
	this->_expn = expn;
}


ListNode::~ListNode()
{
}
