#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	int index;
	int data;
	Node *pLChild;
	Node *pRChild;
	Node *pParent;

	Node();
	~Node();
	Node *SearchNode(int nodeIndex);
	void DeleteNode();
	void PreorderTraversal();
	void InorderTraversal();
	void PostorderTraversal();	

};

#endif