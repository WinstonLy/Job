/**
 * 定义栈的链式存储结构
 */

#ifndef __LIST_H__
#define __LIST_H__

#include "Node.h"
class Stack
{
public:
	Stack();
	~Stack();

	void clearStack();
	bool pushStack(Node* node);
	bool popStack(Node* node);
	int getTop();
private:
	int top;
	Node* head;
};
#endif