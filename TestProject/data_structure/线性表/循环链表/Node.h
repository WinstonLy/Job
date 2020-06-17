#ifndef _NODE_H_
#define _NODE_H_

// #include "Person.h"

class Node
{
public:
	int data;
	Node *next;

	Node(int _data);
	~Node();
	void printNode();

};

#endif