#ifndef _TREE_H_
#define _TREE_H_

class Tree
{
public:
	Tree(int size, int *pRoot);
	~Tree();
	int *SearchNode(int nodeIndex);
	bool AddNode(int nodeIndex, int direction, int *pNode);
	bool DeleteNode(int nodeIndex, int *pNode);
	void TreeTraverse();

private:
	int *m_pTree;
	int m_iSize;
};
#endif