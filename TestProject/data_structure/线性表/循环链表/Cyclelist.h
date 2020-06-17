#ifndef __CYCLELIST_H__
#define __CYCLELIST_H__
/**
 * 创建循环链表
 */
#include "Node.h"

class Cyclelist
{
public:
	Cyclelist();
	~Cyclelist();

	void initList(int n);
	void clearList();
	void findAndKillK(int k, int m);
private:
	Node* head;
};


#endif