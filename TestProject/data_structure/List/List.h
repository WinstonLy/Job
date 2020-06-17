#ifndef _LIST_H_
#define _LIST_H_


#include "Coordinate.h"
class CList
{
public:
	CList(int size);
	~CList();
	void ClearList();
	bool ListEmpty();
	int ListLength();
	bool GetElem(int i, Coordinate *elem);
	int LocateElem(Coordinate *elem);
	bool PriorElem(Coordinate *currentElem, Coordinate *preElem);
	bool NextElem(Coordinate *currentElem, Coordinate *nextElem);
	void ListTraverse();
	bool ListInsert(int i, Coordinate *elem);
	bool ListDelete(int i, Coordinate *elem);
private:
	Coordinate *m_pList;
	int m_iSize;
	int m_iLength;
};

#endif