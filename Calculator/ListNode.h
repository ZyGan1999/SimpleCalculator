#pragma once
class ListNode
{
public:
	ListNode();//Ĭ�Ϲ��캯��
	ListNode(const ListNode &node);//���ƹ��캯��
	ListNode(double coef, int expn);//���캯��
	~ListNode();
	double _coef;//ϵ��
	int _expn;//ָ��
	ListNode * _next;//��һ�ڵ�ָ�룬������������ʹ��
	ListNode * _prev;//��һ���ָ�룬������������ʹ��
	bool operator ==(const ListNode & node)const {
		if (this->_coef == node._coef&&this->_expn == node._expn) return true;
		return false;
	}
	ListNode operator -()const {//��������
		ListNode ret(-_coef, _expn);
		return ret;
	}
};

