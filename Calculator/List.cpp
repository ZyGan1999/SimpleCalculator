#include <iostream>
#include <cmath>
#include "List.h"
using namespace std;
void List::add(const List &poly) {
    for(auto pointer = poly.header->_next; pointer != poly.tailer; pointer = pointer->_next) {
		//�ӷ���ʵ��
        addNode(*pointer);
    }
	for (auto pointer = header->_next; pointer != tailer; pointer = pointer->_next) {
		//ɾ��ϵ��Ϊ0�Ľ��
		if (pointer->_coef == 0) {
			ListNode * del = pointer;
			pointer = pointer->_prev;
			deleteNode(del);
		}
	}
}

void List::minus(const List &poly) {
    for(auto pointer = poly.header->_next; pointer != poly.tailer; pointer = pointer->_next) {
		//������ʵ��
        add(-pointer->_coef, pointer->_expn);
    }
	for (auto pointer = header->_next; pointer != tailer; pointer = pointer->_next) {
		//ɾ��ϵ��Ϊ0�Ľ��
		if (pointer->_coef == 0) {
			ListNode * del = pointer;
			pointer = pointer->_prev;
			deleteNode(del);
		}
	}
}

void List::add(double coef, int expn) {
    addNode(ListNode(coef, expn));
	for (auto pointer = header->_next; pointer != tailer; pointer = pointer->_next) {
		if (pointer->_coef == 0) {
			ListNode * del = pointer;
			pointer = pointer->_prev;
			deleteNode(del);
		}
	}
}

void List::multiply(const List & poly, List & result)
{
	//������
	for (auto n = poly.header->_next; n != poly.tailer; n = n->_next) {
		for (auto p = header->_next; p != tailer; p = p->_next) {
			p->_coef *= n->_coef;
			p->_expn += n->_expn;
		}
	}
	//�������򣬺ϲ�ͬ����
	for (auto p = header->_next; p != tailer; p = p->_next) {
		result.addNode(*p);
	}
}

void List::Derivation()
{
	//ϵ����ָ���ı仯
	for (auto curP = header->_next; curP != tailer; curP = curP->_next) {
		curP->_coef = curP->_coef * curP->_expn;
		curP->_expn--;
	}
	//0�Ϳձ���ж�
	if (header->_next!=tailer && header->_next->_expn < 0) {
		deleteNode(header->_next);
	}
}

void List::addNode(const ListNode& node) {
	//�ӽ��
	//�ӷ��������ʵ�ֻ���
    for(auto pointer = header->_next; pointer != nullptr; pointer = pointer->_next) {
        if(pointer->_expn == node._expn) {
            pointer->_coef += node._coef;
            break;
        }
        else if(node._expn < pointer->_expn) {
            auto cache = new ListNode(node);
            cache->_prev = pointer->_prev;
            cache->_next = pointer;
            pointer->_prev->_next = cache;
            pointer->_prev = cache;
            break;
        }
    }
}

void List::deleteNode(ListNode * node)
{
	//ɾ���ڵ�
	//����ɾ��ϵ��Ϊ0�Ľ��
	bool flag = false;
	for (auto p = header->_next; p != tailer; p = p->_next) {
		if (p == node) flag = true;
	}
	if (!flag) exit(2);
	node->_prev->_next = node->_next;
	node->_next->_prev = node->_prev;
	free(node);
}


void List::print() const {
	//�������
	if (header->_next == tailer) {
		cout << 0 << endl;
		return;
	}
	bool flag = true;
	for (auto cache = tailer->_prev; cache != header; cache = cache->_prev) {
		if (flag) {
			flag = false;
			cout << cache->_coef << "*x" << '^' << cache->_expn;
		}
		else {
			if (cache->_coef > 0) {
				cout << "+";
			}
			cout << cache->_coef; 
			if(cache->_expn > 0) cout<< "*x" << '^' << cache->_expn;
		}
	}
	cout << endl;
}
