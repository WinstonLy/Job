#include "Tree.h"
#include <cstdlib>
#include <iostream>

using namespace std;
Tree::Tree()
{
	m_pRoot = new Node();
}

Tree::~Tree()
{
	// DeleteNode(0, NULL);
	m_pRoot->DeleteNode();
}

Node *Tree::SearchNode(int nodeIndex)
{
	// cout << "search node" << endl;
	return m_pRoot->SearchNode(nodeIndex);
}

bool Tree::AddNode(int nodeIndex, int direction, Node *pNode)
{
	// cout << "addnode" << endl;
	// cout << nodeIndex << endl;
	Node *temp = SearchNode(nodeIndex);
	// cout << "temp" << temp->data << temp->index << endl;
	if(temp == NULL)
	{
		return false;
	} 
	// cout << temp->data << temp->index << endl;
	// cout << "2" << endl;
	Node *node = new Node();
	if(node == NULL)
	{
		return false;
	}

	node->data = pNode->data;
	node->index = pNode->index;
	//cout << node->data << endl;
	if(direction == 0)
	{
		// cout << "3" << endl;
		temp->pLChild = node;
		// cout << temp->pLChild->index << endl;
		// cout << "31" << endl;
	}
	if(direction == 1)
	{
		temp->pRChild = node;
		// cout << temp->pRChild->index << endl;

	} 
	// cout << "4" << endl;
	return true;

}

bool Tree::DeleteNode(int nodeIndex, Node *pNode)
{
	Node *temp = SearchNode(nodeIndex);
	if(temp == NULL)
	{
		return false;
	}
	if(pNode != NULL)
	{
		pNode->data = temp->data;
	}
	cout << temp->index << endl;
	temp->DeleteNode();

	return true;
}
void Tree::PreorderTraversal()	
{
	// cout << "5" << endl;
	m_pRoot->PreorderTraversal();
}
void Tree::InorderTraversal()
{
	m_pRoot->InorderTraversal();
}
void Tree::PostorderTraversal()
{
	m_pRoot->PostorderTraversal();
}