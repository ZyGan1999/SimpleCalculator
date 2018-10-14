#ifndef LIST_LIST_H
#define LIST_LIST_H
#include "ListNode.h"
class List {
public:
    List() {
		//构造函数
		//双向链表
        header = new ListNode(0, -INF);
        tailer = new ListNode(0,  INF);
        header->_next = tailer;
        tailer->_prev = header;
    }
	void addNode(const ListNode& node);//插入结点，按照指数升序插入
	void deleteNode(ListNode * node);//删除指定指针指向的结点
    void add(const List & poly);//链表多项式的加法
    void minus(const List & poly);//链表多项式的减法
    void add(double coef, int expn);//加法重载，类似插入结点
	void multiply(const List & poly,List & result);
	void Derivation();//求导一次
    void print() const;//输出多项式

private:

    static const int INF = 0x7fffffff;

    ListNode * header;//头结点
    ListNode * tailer;//尾结点


};


#endif //LIST_LIST_H
