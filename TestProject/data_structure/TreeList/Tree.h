#ifndef _TREE_H_
#define _TREE_H_

#include "Node.h"

class Tree
{
public:
	Tree();		// 创建树
	~Tree();	// 销毁树
	Node *SearchNode(int nodeIndex);	// 搜索节点
	bool AddNode(int nodeIndex, int direction, Node *pNode);	// 添加节点
	bool DeleteNode(int nodeIndex, Node *pNode);	// 删除节点
	void PreorderTraversal();	// 前序遍历
	void InorderTraversal();	// 中序遍历
	void PostorderTraversal();	// 后序遍历


private:
	Node *m_pRoot;
};

#endif