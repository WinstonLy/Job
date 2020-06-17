#include <iostream>
#include "Stack.h"
#include "Node.h"

using namespace std;

int main()
{
	Stack* stack = new Stack;
	Node* node = new Node(0);

	for(int i = 0; i < 6; ++i)
	{
		node->data = i;
		
		stack->pushStack(node);
	}
	Node* temp = node;
	for(int i = 0; i < 6; ++i)
	{
		cout << "Top" << stack->getTop() << endl;
		stack->popStack(temp);
		cout << "pop" << temp->data << endl;
	}

	delete stack;
	stack = NULL;
	delete node;
	node = NULL;

	return 0;

}