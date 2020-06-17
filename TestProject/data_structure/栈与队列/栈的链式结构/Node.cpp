#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(int _data)
{
	data = _data;
}

Node::~Node()
{

}

void Node::printNode()
{
	cout << data << endl;
}