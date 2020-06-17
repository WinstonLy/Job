#ifndef __LIST_H__
#define __LIST_H__

/**
 * 创建线性表的顺序存储结构
 */
template <typename T> 
class List
{
public:
	List(int _size);					/* 构造函数，初始化 */
	~List();							/* 析构函数，释放内存 */

	void clearList();					/* 清楚线性表 */
	bool listEmpty();					/* 判断线性表是否为空 */
	int getListLength();				/* 获取线性表的长度 */

	bool getElem(int i, T& elem);		/* 获取下标为 i 的元素值 */
	int locateElem(T &elem);			/* 获取元素 elem 在线性表中的位置 */

	bool priorElem(T& currentElem, T& preElem);		/* 获取指定元素 currentElem 的直接前驱 */
	bool nextElem(T& currentElem, T& nextElem);			/* 获取指定元素 currentElem 的直接后继 */

	bool listInsertHead(T& elem);		/* 在线性表头部插入元素 elem */
	bool listInsert(int i, T& elem);	/* 在下标 i 处插入元素 elem */
	bool listDelete(int i, T& elem);	/* 删除下标为 i 的元素 */
	void listTraverse();				/* 遍历线性表 */


private:
	T* m_pList;
	int m_iSize;
	int m_iLength;
};


#endif
