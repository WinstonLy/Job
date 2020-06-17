#include <iostream>
#include "Stack.h"
#include "Node.h"

using namespace std;

Stack::Stack()
{
	top = 0;
	head = new Node(0);
	head->next = NULL;
}
Stack::~Stack()
{
	clearStack();
	delete head;
	head->next = NULL;
}
	
void Stack::clearStack()
{
	Node* temp = new Node(0);
	temp = head;
	if(top == 0)
	{
		cout << "Stack is empty" << endl;
		return;
	}
	while(temp)
	{
		Node* t = temp;
		if(temp->next)
		{
			t = temp->next;
			delete temp;
			temp = t;
		}
		delete temp;
		temp = NULL;
	}

	delete temp;
	temp = NULL;
}
bool Stack::pushStack(Node* node)
{
	

	++top;

	Node* temp = new Node(0);
	temp->data = node->data;
	temp->next = head;
	head = temp;
	
	return true;
}
bool Stack::popStack(Node* node)
{
	if(top == 0)
	{
		cout << "stack is empty" << endl;
		return false;
	}

	Node* temp = new Node(0);
	temp = head;
	node->data = temp->data;

	Node* t = temp->next;
	head = t;
	delete temp;
	temp = NULL;
	
	--top;
	return true;

}
int Stack::getTop()
{
	return top;
}