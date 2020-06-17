#include <iostream>
#include "List.h"
#include "Coordinate.h"

using namespace std;

CList::CList(int size)
{
	m_iSize = size;
	m_pList = new Coordinate[m_iSize];
	m_iLength = 0;
}


CList::~CList()
{
	delete []m_pList;
	m_pList = NULL;
}

void CList::ClearList()
{
	m_iLength = 0;
}

bool CList::ListEmpty()
{
	if(0 == m_iLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CList::ListLength()
{
	return m_iLength;
}
bool CList::GetElem(int i, Coordinate *elem)
{
	if(i < 0 || i > m_iSize)
	{
		return false;
	}

	*elem = m_pList[i];
	return true;
}
int CList::LocateElem(Coordinate *elem)
{
	for(int i = 0; i < m_iLength; i++)
	{
		if(m_pList[i] == *elem)
		{
			return i;
		}

	}

	return -1;
}

bool CList::PriorElem(Coordinate *currentElem, Coordinate *preElem)
{
	int temp = LocateElem(currentElem);
	if(-1 == temp)
	{
		return false;
	}
	else
	{
		if(0 == temp)
		{
			return false;
		}
		else
		{
			*preElem = m_pList[temp - 1];
			return true;
		}
	}
}

bool CList::NextElem(Coordinate *currentElem, Coordinate *nextElem)
{
	int temp = LocateElem(currentElem);
	if(-1 == temp)
	{
		return false;	
	}
	else
	{
		if(m_iLength - 1 == temp)
		{
			return false;
		}
		else
		{
			*nextElem = m_pList[temp + 1];
			return true;
		}
	}
}

void CList::ListTraverse()
{
	for(int i = 0; i < m_iLength; i++)
	{
		cout << m_pList[i] << endl;
	}
}

bool CList::ListInsert(int i, Coordinate *elem)
{
	if(i < 0 || i > m_iLength)
	{
		return false;
	}
	
	m_iLength++;
	
	for(int k = m_iLength - 1; k > i; k--)
	{
		m_pList[k] = m_pList[k - 1];
	}
	
	m_pList[i] = *elem;
	
	return true;
}

bool CList::ListDelete(int i, Coordinate *elem)
{
	if(i < 0 || i >= m_iLength)
	{
		return false;
	}

	*elem = m_pList[i];
	m_iLength--;
	
	for(int k = i; k < m_iLength; k++)
	{
		m_pList[k] = m_pList[k + 1];
	}

	
	return true;
}

