/**
 * 创建线性表的链式存储结构
 */
#ifndef __LIST_H__
#define __LIST_H__

template <typename T> 
class List
{
public:
	List();								/* 构造函数，初始化 */
	~List();							/* 析构函数，释放内存 */

	void clearList();					/* 清除线性表 */
	bool listEmpty();					/* 判断线性表是否为空 */
	int getListLength();				/* 获取线性表的长度 */

	T* getElem(int i);		/* 获取下标为 i 的元素值 */
	int locateElem(T *elem);			/* 获取元素 elem 在线性表中的位置 */

	T* priorElem(T* currentElem);		/* 获取指定元素 currentElem 的直接前驱 */
	T* nextElem(T* currentElem);			/* 获取指定元素 currentElem 的直接后继 */

	bool listInsertHead(T* elem);		/* 在线性表头部插入元素 elem */
	bool listInsert(int i, T* elem);	/* 在下标 i 处插入元素 elem */
	bool listDelete(int i, T* elem);	/* 删除下标为 i 的元素 */
	void listTraverse();				/* 遍历线性表 */


private:
	T* m_pNode;			/* 存储链表的结点 */
	int m_iLength;		/* 链表长度 */
};


#endif