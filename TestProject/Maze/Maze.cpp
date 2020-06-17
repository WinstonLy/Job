#include <iostream>
#include <cstdlib>

using namespace std;
#define MAX_ROW 5
#define MAX_COL 5

int MazeArray[MAX_ROW][MAX_COL] = {
				0, 1, 0, 0, 0,
				0, 1, 0, 1, 0,
				0, 0, 0, 0, 0,
				0, 1, 1, 1, 0,
				0, 0, 0, 1, 0,
};


class Node
{
public:
	Node();
	~Node();

	int row;
	int col;


};

class Maze
{
public:
	Maze();
	~Maze();
	void PushStack(Node *node);
	Node *PopStack();
	void PrintMaze();
	bool StackEmpty();

	int top;	
	Node m_pNode[520];
};


Node::Node()
{
	row = 0;
	col = 0;
}

Node::~Node()
{

}

Maze::Maze()
{
	//Node *m_pNode = new Node(0, 0);
	Node m_pNode[520];
	top = 0;
}

Maze::~Maze()
{
	
}

void Maze::PushStack(Node *node)
{
	m_pNode[top++];
	m_pNode[top].row = node->row;
	m_pNode[top].col = node->col;
	
}
Node *Maze::PopStack()
{
	Node *temp = new Node();
	temp = &m_pNode[top];
	
	top--;

	return temp;

}

void Maze::PrintMaze()
{
	for(int i = 0; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COL; j++)
		{
			cout << MazeArray[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "/**********************/" << endl;
}

bool Maze::StackEmpty()
{
	if(0 == top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(void)
{
	Node *node = new Node();
	Node *temp = new Node();
	Maze *maze = new Maze();
	MazeArray[node->row][node->col] = 2;
	

	maze->PrintMaze();
	maze->PushStack(node);

	while(!maze->StackEmpty())
	{
		temp = maze->PopStack();
		if(temp->row == MAX_ROW - 1 && temp->col == MAX_COL - 1)
		{
			cout << "success" << endl;
			break;
		}
		if(temp->col + 1 < MAX_COL&& MazeArray[temp->row][temp->col + 1] == 0)
		{
			MazeArray[temp->row][temp->col + 1] = 2;
			node->row = temp->row;
			node->col = temp->col + 1;
			maze->PushStack(node);
		}
		if(temp->col - 1 > 0 && MazeArray[temp->row][temp->col - 1] == 0)
		{
			MazeArray[temp->row][temp->col - 1] = 2;
			node->row = temp->row;
			node->col = temp->col - 1;
			maze->PushStack(node);
		}
		if(temp->row + 1 < MAX_ROW&& MazeArray[temp->row + 1][temp->col] == 0)
		{
			MazeArray[temp->row + 1][temp->col] = 2;
			node->row = temp->row + 1;
			node->col = temp->col;
			maze->PushStack(node);
		}
		if(temp->row - 1 < MAX_ROW&& MazeArray[temp->row - 1][temp->col] == 0)
		{
			MazeArray[temp->row - 1][temp->col] = 2;
			node->row = temp->row - 1;
			node->col = temp->col;
			maze->PushStack(node);
		}
		maze->PrintMaze();
	}

	return 0;
}