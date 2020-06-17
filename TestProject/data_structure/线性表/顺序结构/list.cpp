/**
 * 顺序表的函数实现
 */
#include <iostream>
#include "list.h"

using namespace std;
/**
 * 构造函数，初始化 
 */
template <typename T>
List<T>::List(int _size)
{
	m_pList = new T();
	m_iSize = _size;
	m_iLength = 0;
	// cout << m_iSize << endl;
}	

/**
 * 析构函数，释放内存 
 */
template <typename T>
List<T>::~List()
{
	delete m_pList;
	m_pList = NULL;
	m_iLength = 0;
}

/**
 * 清除线性表
 */
template <typename T>
void List<T>::clearList()
{
	m_iLength = 0;
}

/**
 * 判断线性表是否为空
 * @return 成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::listEmpty()
{
	if(m_iLength == 0)
		return true;
	return false;
}

/**
 * 获取线性表的长度
 * @return 返回线性表的长度
 */
template <typename T>
int List<T>::getListLength()
{	
	return m_iLength;
}

/**
 * [获取下标为 i 的元素值]
 * @param  i    指定元素下标
 * @param  elem 将下标为 i 的元素保存在 elem中
 * @return      成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::getElem(int i, T& elem)
{
	if(i < 0 || i >= m_iLength)
		return false;

	elem = m_pList[i];

	return true;

}

/**
 * 获取元素 elem 在线性表中的位置
 * @param  elem 待获取的元素值
 * @return      找到 elem 返回位置下标，没找到返回 -1
 */
template <typename T>
int List<T>::locateElem(T &elem)
{
	if(listEmpty())
		return -1;

	for(int i = 0; i < m_iLength; ++i)
	{
		if(m_pList[i] == elem)
			return i;
	}

	return -1;
}

/**
 * 获取指定元素 currentElem 的直接前驱
 * @param  currentElem 当前位置元素
 * @param  preElem     保存直接前驱元素
 * @return             成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::priorElem(T& currentElem, T& preElem)
{
	int k = locateElem(currentElem);

	if(k == -1 || k == 0)
	{
		return false;	/* 如果线性表为空，或者currentElem 为头部元素，没有前驱，返回 false */
	}
	else
	{
		preElem = m_pList[k - 1]; 
		return true;
	}
}

/**
 * 获取指定元素 currentElem 的直接后继
 * @param  currentElem  指定当前位置的元素
 * @param  nextElem 	保存当前元素的直接后继元素
 * @return          	成功返回
 */
template <typename T>
bool List<T>::nextElem(T& currentElem, T& nextElem)
{
	int k = locateElem(currentElem);

	if(k == -1 || k == m_iLength - 1)
	{
		return false;	/* 如果线性表为空，或者currentElem 为尾部元素，没有后继，返回 false */
	}
	else
	{
		nextElem = m_pList[k + 1]; 
		return true;
	}
}

/**
 * 在线性表头部插入元素 elem
 * @param  elem 待插入元素
 * @return      成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::listInsertHead(T& elem)
{
	++m_iLength;
	for(int i = m_iLength - 1; i > 0; --i)
	{
		m_pList[i] = m_pList[i - 1];
	}

	m_pList[0] = elem;

	return true;
}

/**
 * 在下标 i 处插入元素 elem
 * @param  i    待插入元素位置
 * @param  elem 待插入元素
 * @return      成功返回 true，失败返回 false
 */
template <typename T>
bool List<T>::listInsert(int i, T& elem)
{
	if(i < 0 || i > m_iLength)
		return false;

	++m_iLength;
	if(i == 0)
	{
		listInsertHead(elem);
		return true;
	}

	for(int k = m_iLength - 1; k > i; --k)
	{
		m_pList[k] = m_pList[k - 1];
	}
	m_pList[i] = elem;

	return true;
}

/**
 * 删除下标为 i 的元素
 * @param  i    删除元素的下标
 * @param  elem 保存删除的元素
 * @return      成功返回 true，失败返回false
 */
template <typename T>
bool List<T>::listDelete(int i, T& elem)
{
	if(i < 0 || i >= m_iLength)
		return false;

	elem = m_pList[i];
	
	--m_iLength;
	for(int k = i; k < m_iLength; ++k)
	{
		m_pList[k] = m_pList[k + 1];
	}

	return true;
}

/**
 * 遍历线性表
 */
template <typename T>
void List<T>::listTraverse()
{
	if(listEmpty())
		return;
	// cout << "顺序线性表遍历结果如下：" << endl;
	for(int i = 0; i < m_iLength; ++i)
	{
		cout << m_pList[i] << endl;
	}
}
