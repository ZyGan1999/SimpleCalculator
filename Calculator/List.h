#ifndef LIST_LIST_H
#define LIST_LIST_H
#include "ListNode.h"
class List {
public:
    List() {
		//���캯��
		//˫������
        header = new ListNode(0, -INF);
        tailer = new ListNode(0,  INF);
        header->_next = tailer;
        tailer->_prev = header;
    }
	void addNode(const ListNode& node);//�����㣬����ָ���������
	void deleteNode(ListNode * node);//ɾ��ָ��ָ��ָ��Ľ��
    void add(const List & poly);//�������ʽ�ļӷ�
    void minus(const List & poly);//�������ʽ�ļ���
    void add(double coef, int expn);//�ӷ����أ����Ʋ�����
	void multiply(const List & poly,List & result);
	void Derivation();//��һ��
    void print() const;//�������ʽ

private:

    static const int INF = 0x7fffffff;

    ListNode * header;//ͷ���
    ListNode * tailer;//β���


};


#endif //LIST_LIST_H
