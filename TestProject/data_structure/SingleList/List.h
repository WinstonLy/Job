/**
 * 创建线性表的链式存储结构
 */
#ifndef __LIST_H__
#define __LIST_H__

class List 
{
public:
	List();
	~List();
	void ClearList();
	bool ListEmpty();
	int ListLength();
	bool GetElem(int i, Node *pNode);
	int LocateElem(Node *pNode);
	bool PriorElem(Node *pCurrentNode, Node *pPreNode);
	bool NextElem(Node *pCurrentNode, Node *pNextNode);
	void ListTraverse();
	bool ListInsert(int i, Node *pNode);
	bool ListDelete(int i, Node *pNode);
	bool ListInsertHead(Node *pNode);
	bool ListInsertTail(Node *pNode);



private:
	Node *m_pList;
	int m_iLength;

};

#endif