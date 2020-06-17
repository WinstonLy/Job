#include <iostream>
#include "list.cpp"
#include "Node.h"
using namespace std;

int main()
{

	Node* node0 = new Node(2);
	Node* node1 = new Node(7);
	Node* node2 = new Node(6);
	Node* node3 = new Node(3);
	Node* node4 = new Node(25);

	List<Node>* list = new List<Node>();

	if(list->listEmpty())
		cout << "list is empty" << endl;

	list->listInsertHead(node0);
	cout << "listInsertHead" << endl;
	list->listInsert(1, node1);
	list->listInsert(2, node2);
	list->listInsertHead(node3);
	list->listInsert(4, node4);

	if(!list->listEmpty())
		cout << "list is not empty" << endl;

	list->clearList();
	if(list->listEmpty())
		cout << "list is empty" << endl;
	
	// cout << "getElem:" << endl;
	// cout << list->getElem(1)->data << endl;

	// cout << "locateElem" << endl;
	// cout << list->locateElem(node0) << endl;

	// Node* temp = new Node(6);
	// // cout << "priorElem" << endl;
	// // cout << list->priorElem(temp)->data << endl;

	// // cout << "nextElem" << endl;
	// // cout << list->nextElem(temp)->data << endl;
	
	// cout << "deleteElem" << endl;
	// list->listDelete(2, temp);
	// cout << temp->data << endl;
	
	// list->listTraverse();

	// delete temp;
	// temp = NULL;
	delete node0;
	node0 = NULL;
	delete node1;
	node1 = NULL;
	delete node2;
	node2 = NULL;
	delete node3;
	node3 = NULL;
	delete node4;
	node4 = NULL;
	delete list;
	list = NULL;
	return 0;
}