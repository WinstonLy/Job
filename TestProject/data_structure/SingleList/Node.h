#ifndef _NODE_H_
#define _NODE_H_

#include "Person.h"

class Node
{
public:
	Person data;
	Node *next;

	void PrintNode();

};

#endif