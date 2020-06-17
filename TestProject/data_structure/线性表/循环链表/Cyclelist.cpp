#include <iostream>
#include "Cyclelist.h"

using namespace std;

Cyclelist::Cyclelist()
{
	head = new Node(1);
	head->next = NULL;

}
Cyclelist::~Cyclelist()
{
	clearList();
	delete head;
	head = NULL;
}

void Cyclelist::clearList()
{
	Node * temp = head->next;
	while(temp != temp->next)
	{
		Node * t = temp->next;
		delete temp;
		temp = t;
	}

	delete temp;
	temp = NULL;
}
void Cyclelist::initList(int n)
{
	Node * temp = head;
	for(int i = 1; i < n; ++i)
	{
		Node *node = new Node(1);
		node->data = i + 1;
		node->next = NULL;
		temp->next = node;
		temp = temp->next;
	}
	temp->next = head;

	// Node*t = head;
	// while(t != t->next)
	// {
	// 	cout << t->data << endl;
	// 	t = t->next;
	// }
}


/** 约瑟夫环问题，是一个经典的循环链表问题，
题意是：已知 n 个人（分别用编号 1，2，3，…，n 表示）围坐在一张圆桌周围，
从编号为 k 的人开始顺时针报数，数到 m 的那个人出列；他的下一个人又从 1 开始，
还是顺时针开始报数，数到 m 的那个人又出列；依次重复下去，直到圆桌上剩余一个人 */
void Cyclelist::findAndKillK(int k, int m)
{
	/* 找到当前结点的上一结点 */
	Node* tail = head;
	while(tail->next != head)
	{
		tail = tail->next;
	}
	/* 找到编号为 k 的结点*/
	Node* temp = head;
	while(temp->data != k)
	{
		tail = temp;
		temp = temp->next;
	}

	/* 开始报数 */
	while(temp != temp->next)
	{
		for(int i = 1; i < m; ++i)
		{
			tail = temp;
			temp = temp->next;
		}
		tail->next = temp->next;
		cout << "出列的元素：" << temp->data << endl;
		delete temp;
		temp = tail->next;
	}

	cout << "胜出元素：" << temp->data << endl;
	delete temp;
	temp = NULL;
}
