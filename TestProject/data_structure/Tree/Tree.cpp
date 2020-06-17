#include "Tree.h" 
#include <cstdlib>
#include <iostream> 

using namespace std;

/******* 创建Tree *******/
Tree::Tree(int size, int *pRoot)
{
	m_iSize = size;
	m_pTree = new int[m_iSize];
	for(int i = 0; i < m_iSize; i++)
	{
		m_pTree[i] = 0;
	}

	m_pTree[0] = *pRoot;

}
/******* 销毁Tree *******/
Tree::~Tree()
{
	delete []m_pTree;
	m_pTree = NULL;
}
/******* 根据索引搜索节点 *******/
int *Tree::SearchNode(int nodeIndex)
{
	if(nodeIndex < 0 || nodeIndex > m_iSize)
	{
		return NULL;
	}
	if(m_pTree[nodeIndex] == 0)
	{
		return NULL;
	}

	return &m_pTree[nodeIndex];
}
/******* 添加树节点 *******/
/* direction = 0 ： 左节点 */
/* direction = 0 ：　右节点　*/
bool Tree::AddNode(int nodeIndex, int direction, int *pNode)
{
	if(nodeIndex < 0 || nodeIndex >= m_iSize)
	{
		return false;
	}
	if(0 == m_pTree[nodeIndex])
	{
		return false;
	}

	if(0 == direction)
	{
		if(nodeIndex * 2 + 1 >= m_iSize)
		{
			return false;
		}
		if(0 != m_pTree[nodeIndex * 2 + 1])
		{
			return false;
		}

		m_pTree[nodeIndex * 2 + 1] = *pNode;
	}
	if(1 == direction)
	{
		if(nodeIndex * 2 + 2 >= m_iSize)
		{
			return false;
		}
		if(0 != m_pTree[nodeIndex * 2 + 2])
		{
			return false;
		}

		m_pTree[nodeIndex * 2 + 2] = *pNode;
	}
	
	return true;

}
/******* 删除节点 *******/
bool Tree::DeleteNode(int nodeIndex, int *pNode)
{
	if(nodeIndex < 0 || nodeIndex > m_iSize)
	{
		return NULL;
	}
	if(m_pTree[nodeIndex] == 0)
	{
		return NULL;
	}

	*pNode = m_pTree[nodeIndex];
	m_pTree[nodeIndex] = 0;

	return 0;
}
/******* 遍历Tree *******/
void Tree::TreeTraverse()
{
	for(int i = 0; i < m_iSize; i++)
	{
		cout << m_pTree[i] << " ";
	}
	cout << endl;
}