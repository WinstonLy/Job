#include "Tree.h"
#include <iostream>

using namespace std;

int main(void)
{
/*			(0)
	5(1)			8(2)
2(3)	6(4)	9(5)	7(6)
*/
	Node *node1 = new Node();
	node1->index = 1;
	node1->data = 5;

	Node *node2 = new Node();
	node2->index = 2;
	node2->data = 8;
	
	Node *node3 = new Node();
	node3->index = 3;
	node3->data = 2;
	
	Node *node4 = new Node();
	node4->index = 4;
	node4->data = 6;
	
	Node *node5 = new Node();
	node5->index = 5;
	node5->data = 9;

	Node *node6 = new Node();
	node6->index = 6;
	node6->data = 7;

	Tree *tree = new Tree();

	tree->AddNode(0, 0, node1);
	tree->AddNode(0, 1, node2);
	
	tree->AddNode(1, 0, node3);
	tree->AddNode(1, 1, node4);
	
	tree->AddNode(2, 0, node5);
	tree->AddNode(2, 1, node6);

	// tree->InorderTraversal();
	tree->PostorderTraversal();

	Node *temp = new Node();
	tree->DeleteNode(3,temp);
	tree->PostorderTraversal();
	delete tree;
	tree = NULL;

	return 0;

}