/**
 * 线性表链式存储的具体实现
 */
#include <iostream>
#include "list.h"

using namespace std;
/**
 * 构造函数，初始化
 */
template <typename T>
List<T>::List()
{
	m_pNode = new T(0);
	m_pNode->next = NULL;
	m_iLength = 0;
}

/**
 * 析构函数，释放内存
 */
template <typename T>
List<T>::~List()
{
	clearList();

	delete m_pNode;
	m_pNode = NULL;
}	

/**
 * 清除线性表
 */
template <typename T>
void List<T>::clearList()
{
	T* currentNode = m_pNode->next;
	while(currentNode)
	{
		T* temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}

	m_iLength = 0;
	m_pNode->next = NULL;
}

/**
 * 判断线性表是否为空
 * @return 线性表为空返回 true，不为空返回 false
 */
template <typename T>
bool List<T>::listEmpty()
{
	if(0 == m_iLength)
		return true;

	return false;
}

/**
 * 获取线性表的长度
 * @return 返回线性表的长度，为空返回 0
 */
template <typename T>
int List<T>::getListLength()
{
	return m_iLength;
}

/**
 * 获取指定下标 i 处的元素
 * @param  i 指定获取位置下标
 * @return   存在元素返回元素
 */
template <typename T>
T* List<T>::getElem(int i)
{
	T* tempNode = NULL;
	if(i < 0 || i >= m_iLength)
		return tempNode;

	tempNode = m_pNode;
	for(int k = 0; k < i; ++k)
	{
		tempNode = tempNode->next;
	}

	return tempNode;
}	

/**
 * 获取元素 elem 在线性表中的位置
 * @param  elem 指定元素
 * @return      成功返回元素下标，失败返回 -1
 */
template <typename T>
int List<T>::locateElem(T *elem)
{
	int index = 0;
	T* tempNode = m_pNode;
	while(tempNode)
	{
		if(tempNode->data == elem->data)
		{
			return index;

		}
		if(tempNode->next)
		{
			tempNode = tempNode->next;
			++index;
		}

	}

	return -1;
}

/**
 * 获取指定元素 currentElem 的直接前驱
 * @param  currentElem 
 * @return     返回指定元素的前驱
 */
template <typename T>
T* List<T>::priorElem(T* currentElem)
{
	T* preNode = NULL;
	T* tempNode = m_pNode;

	int k = locateElem(currentElem);
	// cout << "k" << k << endl;
	if(k == 0 || k == -1)
		return preNode;
	// cout << "preNode" << endl;
	/** 保存前一个结点，比较当前结点与 currentElem */
	while(tempNode)
	{
		preNode = tempNode;
		if(tempNode->next)
			tempNode = tempNode->next;
		if(tempNode->data == currentElem->data)
			return preNode;
		return preNode;
	}
}

/**
 * 获取指定元素 currentElem 的直接后继
 * @param  currentElem 
 * @return    成功返回指定元素的直接后继，失败返回 -1
 */
template <typename T>
T* List<T>::nextElem(T* currentElem)
{
	T* nextNode = NULL;
	T* tempNode = m_pNode;

	int k = locateElem(currentElem);

	if(k == m_iLength - 1 || k == -1)
		return nextNode;

	/** 比较当前结点与 currentElem */
	while(tempNode)
	{
		if(tempNode->data == currentElem->data)
			return tempNode->next;
		if(tempNode->next)
			tempNode = tempNode->next;
	}
}

/**
 * 在线性表头部插入元素 elem
 * @param  elem 待插入元素
 * @return      成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::listInsertHead(T* elem)
{
	if(listEmpty())
	{
		m_pNode->data = elem->data;
		m_pNode->next = NULL;
		++m_iLength;
		return true;
	}

	T* tempNode = new T(0);
	tempNode->data = elem->data;
	tempNode->next = m_pNode;
	
	m_pNode = tempNode;
	++m_iLength;

	return true;
}

/**
 * 在下标 i 处插入元素 elem
 * @param  i    下标
 * @param  elem 元素
 * @return      成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::listInsert(int i, T* elem)
{
	if(i < 0 || i > m_iLength)
		return false;

	if(i == 0)
	{
		listInsertHead(elem);
		return true;
	}

	T* preNode = new T(0);
	T* tempNode = m_pNode;

	for(int k = 0; k < i; ++k)
	{
		if(tempNode->next)
			tempNode = tempNode->next;
	}
	
	preNode->data = elem->data;
	preNode->next = tempNode->next;
	tempNode->next = preNode;
	++m_iLength;

	return true;
}

/**
 * 删除下标为 i 的元素 
 * @param  i    下标
 * @param  elem 保存删除的元素
 * @return      成功返回 true，失败返回 false
 */
template <typename T>   
bool List<T>::listDelete(int i, T* elem)
{
	if(i < 0 || i >= m_iLength)
		return false;
	if(i == 0)
	{
		elem->data = m_pNode->data;
		m_pNode = m_pNode->next;
		return true;
	}
	T* preNode = new T(0);
	// cout << getElem(i)->data << endl;
	preNode = priorElem(getElem(i));
	// cout << preNode->data << endl;
	T* tempNode = new T(0);
	tempNode = preNode->next;
	elem->data = tempNode->data;

	preNode->next = tempNode->next;

	return true;

}

/**
 * 遍历线性表
 */
template <typename T>
void List<T>::listTraverse()
{
	
	T* tempNode = m_pNode;

	while(tempNode)
	{
		
		tempNode->printNode();
		if(tempNode->next)
			tempNode = tempNode->next;
		else
			break;
	}
}