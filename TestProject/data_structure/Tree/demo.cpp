#include <iostream>
#include "Tree.h"

using namespace std;

int main(void)
{
	int root = 3;
	Tree *tree = new Tree(10, &root);

	int node1 = 5;
	int node2 = 8;
	tree->AddNode(0, 0, &node1);
	tree->AddNode(0, 1, &node2);

	int node3 = 2;
	int node4 = 6;
	tree->AddNode(1, 0, &node3);
	tree->AddNode(1, 1, &node4);

	int node5 = 9;
	int node6 = 7;
	tree->AddNode(2, 0, &node5);
	tree->AddNode(2, 1, &node6);

	tree->TreeTraverse();

	int node = 0;
	tree->DeleteNode(6, &node);
	cout << "delete node = " << node << endl;

	tree->TreeTraverse();
	delete tree;
	tree = NULL;
	return 0;
}