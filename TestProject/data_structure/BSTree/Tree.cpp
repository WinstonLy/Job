/**
 * 二叉树具体实现
 */
#include <iostream>
#include "Tree.h"

using namespace std;
/**
 * 构造函数
 */
// template <typename T>
BSTree::BSTree()
{
	m_pRoot = new BSTNode();
	
}	

/**
 * 析构函数
 */
// template <typename T>
BSTree::~BSTree()
{
	destroy(m_pRoot);
}		

/**
 * [preOrder description]
 * 前序遍历二叉树
 * 外部接口
 */
// template <typename T>
void BSTree::preOrder()
{
	preOrder(m_pRoot);
}		

/**
 * [inOrder description]
 * 中序遍历二叉树
 * 外部接口
 */
// template <typename T> 
void BSTree::inOrder()
{
	inOrder(m_pRoot);
}		

/**
 * [postOrder description]
 * 后序遍历二叉树
 * 外部接口
 */
// template <typename T>
void BSTree::postOrder()
{
	postOrder(m_pRoot);
}	

/**
 * 递归实现查找二叉树中键值为 key 的 node
 * 外部接口
 */
// template <typename T>
BSTNode* BSTree::search(int key)
{
	return search(m_pRoot, key);
}

/**
 * 非递归实现查找二叉树中键值为 key 的 node
 * 外部接口
 */
// template <typename T>
BSTNode* BSTree::iterativeSearch(int key)
{
	return iterativeSearch(m_pRoot, key);
}

/**
 * 查找最小结点
 * @return [返回最小结点的键值]
 * 外部接口
 */
// template <typename T>
BSTNode* BSTree::minNode()
{
	return minNode(m_pRoot);
}

/**
 * 查找最大结点
 * @return [返回最大结点的键值]
 * 外部接口
 */
// template <typename T>
BSTNode* BSTree::maxNode()
{
	return maxNode(m_pRoot);
}

/**
 * 查找 node 的后继结点，即查找二叉树中数据值大于该结点的最小结点
 * 返回后继结点
 */
// template <typename T>
BSTNode* BSTree::successor(BSTNode *node)
{
	/* 如果是最大结点，没有后继结点 */
	if(node->val == maxNode(m_pRoot)->val)
		return NULL;
	/* 获取二叉树中键值为 node->val 的结点 */
	BSTNode *temp = NULL;
	temp = search(m_pRoot, node->val);
	
	if(!temp)
		return NULL;
	/* 如果 temp 有右孩子，后继结点为右孩子中的最小结点 */
	if(temp->RightNode != NULL)
		return minNode(temp->RightNode);
	/* 如果 temp 没有右孩子，分两种情况 */
	
	/* 1. temp 是左孩子，后继结点为父结点 */
	BSTNode *successorNode = temp->parent;
	if(successorNode->LeftNode == temp)
		return successorNode;

	/* 2. temp 是右孩子，后继结点为第一个拥有左结点且不是 temp 的双亲结点 */
	while(successorNode != NULL)
	{
		if(successorNode->LeftNode != NULL && successorNode != temp->parent)
			return successorNode;
		successorNode = successorNode->parent;
	}

	return NULL;
}

/**
 * 查找 node 的前驱结点，即查找二叉树中数据值小于该结点的最大结点
 * 返回前驱结点
 */
// template <typename T>
BSTNode* BSTree::predecessor(BSTNode *node)
{
	/* 如果是最小结点，没有前驱结点 */
	if(node->val == minNode(m_pRoot)->val)
		return NULL;
	
	/* 获取键值为 node->val 的结点 */
	BSTNode *temp = search(m_pRoot, node->val);
	
	if(!temp)
		return NULL;

	/* 如果 temp 有左孩子，前驱结点是左孩子的最大结点 */
	if(temp->LeftNode != NULL)
		return maxNode(m_pRoot);
	
	/* 如果 temp 没有左孩子，有两种情况 */
	/* 1.temp 是右孩子，前驱结点为父结点 */
	BSTNode *predecessorNode = temp->parent;
	if(predecessorNode->RightNode == temp)
		return predecessorNode;
	
	/* 2.temp 是左孩子，前驱结点为第一个拥有右孩子的直接双亲结点 */
	while(predecessorNode != NULL)
	{
		if(predecessorNode->RightNode != NULL && predecessorNode != temp->parent)
			return predecessorNode;

		predecessorNode = predecessorNode->parent;
	}

	return NULL;

}

/**
 * @brief  将结点（键值为 key）插入到二叉树中
 * @note   外部接口
 * @param  key: 
 * @retval 成功返回 TRUE；失败返回 FALSE
 */
// template <typename T>
bool BSTree::insert(int key)
{
	BSTNode *node = new BSTNode();
	if(!node)	
		return false;
	
	node->val = key;
	if(insert(m_pRoot, node))
		return true;

	return false;

}

/**
 * @brief 删除结点（键值为 key） 
 * @note  外部接口
 * @param  key: 
 * @retval 返回删除结点
 */	
// template <typename T>
BSTNode* BSTree::remove(int key)
{
	BSTNode *node = new BSTNode();
	if(!node)
		return NULL;
	
	node->val = key;
	return remove(node);
}

/**
 * @brief 销毁二叉树
 * @note  外部接口，析构函数调用
 * @retval None
 */
// template <typename T>
void BSTree::destroy()
{
	destroy(m_pRoot);
}					

/**
 * @brief  打印二叉树
 * @note   外部接口
 * @retval None
 */
// template <typename T>
void BSTree::print()
{
	// print(m_pRoot);
}

/**
 * @brief 内部使用函数，供类内外部接口调用  
 */

/**
 * @brief  前序遍历"二叉树"
 * @note   供类内外部接口调用
 * @param  tree: 
 * @retval None
 */
// template <typename T>
void BSTree::preOrder(BSTNode* tree) const
{
	if(tree)
	{
		cout << tree->val << endl;
		preOrder(tree->LeftNode);
		preOrder(tree->RightNode);
	}

}

/**
 * @brief  中序遍历二叉树
 * @note   供类内外部接口调用
 * @param  tree: 
 * @retval None
 */
// template <typename T>
void BSTree::inOrder(BSTNode* tree) const
{
	if(tree)
	{
		inOrder(tree->LeftNode);
		cout << tree->val << endl;
		inOrder(tree->RightNode); 
	}
}

/**
 * @brief  后序遍历二叉树 
 * @note   类内外部接口调用
 * @param  tree: 
 * @retval None
 */
// template <typename T>
void BSTree::postOrder(BSTNode* tree) const
{
	if(tree)
	{
		postOrder(tree->LeftNode);
		postOrder(tree->RightNode);
		cout << tree->val << endl;
	}
}

/**
 * @brief  (递归实现)查找"二叉树x"中键值为key的节点
 * @note   类内外部接口调用
 * @param  x: 
 * @param  key: 
 * @retval 
 */
// template <typename T>
BSTNode* BSTree::search(BSTNode* x, int key) const
{
	if(x->val == key)
		return x;
	search(x->LeftNode, key);
	search(x->RightNode, key);
}

/**
 * @brief  (非递归实现)查找"二叉树x"中键值为key的节点
 * @note   类内外部接口调用
 * @param  x: 
 * @param  key: 
 * @retval 
 */
// template <typename T>
BSTNode* BSTree::iterativeSearch(BSTNode* x, int key) const
{

}

/**
 * @brief  查找最小结点
 * @note   类内外部接口调用
 * @param  tree: 
 * @retval 返回tree为根结点的二叉树的最小结点
 */
// template <typename T>
BSTNode* BSTree::minNode(BSTNode* tree)
{
	if(!tree)
		return NULL;
	while(!tree->LeftNode)
	{
		tree = tree->LeftNode;
	}

	return tree;
}

/**
 * @brief  查找最大结点
 * @note   类内外部接口调用
 * @param  tree: 
 * @retval 返回tree为根结点的二叉树的最大结点
 */
// template <typename T>
BSTNode* BSTree::maxNode(BSTNode* tree)
{
	if(!tree)
		return NULL;
	
	while(!tree->RightNode)
	{
		tree = tree->RightNode;
	}

	return tree;
}

/**
 * @brief  将结点(z)插入到二叉树(tree)中
 * @note   类内外部接口调用
 * @param  &tree: 
 * @param  z: 
 * @retval None
 */
// template <typename T>
bool BSTree::insert(BSTNode *tree, BSTNode *z)
{
	if(!tree)
	{
		z->parent = tree;
		tree = z;
		return true;
	}
	if(tree->val > z->val)
	{
		z->parent = tree;
		return insert(tree->LeftNode, z);
	}
	if(tree->val < z->val)
	{
		z->parent = tree;
		return insert(tree->RightNode, z);
	}
}

/**
 * @brief  删除二叉树(tree)中的结点(z)
 * @note    
 * @param  *z: 
 * @retval 并返回被删除的结点
 */
// template <typename T>
BSTNode* BSTree::remove(BSTNode *z)
{
	BSTNode *temp = search(m_pRoot, z->val);
	if(!temp)
		return NULL;

	// BSTNode *node = predecessor(z);
	// temp->parent->
}

/**
 * @brief  销毁二叉树
 * @note   类内外部接口调用
 * @param  &tree: 
 * @retval None
 */
// template <typename T>
void BSTree::destroy(BSTNode *tree)
{
	BSTNode *node = tree;
	delete tree;
	tree = NULL;
	if(node)
	{
		destroy(node->LeftNode);
		destroy(node->RightNode);
	}
	delete node;
	node = NULL;

}					

/**
 * @brief  打印二叉树
 * @note   类内外部接口调用
 * @param  tree: 
 * @param  key: 
 * @param  direction: 
 * @retval None
 */
// template <typename T>
void BSTree::print(BSTNode* tree, int key, int direction)	
{

}                                                                                                                                          


