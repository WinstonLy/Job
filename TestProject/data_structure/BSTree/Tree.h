/**
 * 二叉查找树的建立以及相关操作
 */

#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
/* class node */
// // template <typename T>
class BSTNode
{
public:
	int val;			/* node key */
	BSTNode *LeftNode;	/* left node */
	BSTNode *RightNode; /* right node */
	BSTNode *parent;	/* parent node */
	BSTNode():val(0),LeftNode(NULL),RightNode(NULL),parent(NULL){}; 	/* Constructor with parameters */

};

/* class BSTree */
// // template <typename T>
class BSTree
{
public:
	BSTree();						/* constructor */
	~BSTree();						/* destructor */

	void preOrder();				/* 前序遍历二叉树 */
	void inOrder();					/* 中序遍历二叉树 */
	void postOrder();				/* 后序遍历二叉树 */

	BSTNode* search(int key); /* 递归实现查找二叉树中键值为 key 的 node */
	BSTNode* iterativeSearch(int key);	/* 非递归实现查找二叉树中键值为 key 的 node */

	BSTNode* minNode();					/* 查找最小结点，返回最小结点的键值 */
	BSTNode* maxNode();					/* 查找最大结点，返回最大结点的键值 */

	BSTNode* successor(BSTNode *node);		/* 查找 node 的后继结点，即查找二叉树中数据值大于该结点的最小结点 */
	BSTNode* predecessor(BSTNode *node);	/* 查找 node 的前驱结点，即查找二叉树中数据值小于该结点的最大结点 */

	bool insert(int key);			/* 将结点（键值为 key）插入到二叉树中 */
	BSTNode* remove(int key);			/* 删除结点（键值为 key） */

	void destroy();					/* 销毁二叉树 */
	void print();					/* 打印二叉树 */

private:
	BSTNode *m_pRoot;			/* root node */
	
	/* 内部使用函数，供外部接口调用 */
    void preOrder(BSTNode* tree) const;	/* 前序遍历"二叉树" */
    void inOrder(BSTNode* tree) const;	/* 中序遍历"二叉树" */
    void postOrder(BSTNode* tree) const;	/* 后序遍历"二叉树" */

    BSTNode* search(BSTNode* x, int key) const;				/* (递归实现)查找"二叉树x"中键值为key的节点 */
	BSTNode* iterativeSearch(BSTNode* x, int key) const;	/* (非递归实现)查找"二叉树x"中键值为key的节点 */

	BSTNode* minNode(BSTNode* tree);						/* 查找最小结点：返回tree为根结点的二叉树的最小结点 */
	BSTNode* maxNode(BSTNode* tree);						/* 查找最大结点：返回tree为根结点的二叉树的最大结点 */

	bool insert(BSTNode *tree, BSTNode *z);				/* 将结点(z)插入到二叉树(tree)中 */
	BSTNode* remove(BSTNode *z);		/* 删除二叉树(tree)中的结点(z)，并返回被删除的结点 */

	void destroy(BSTNode *tree);							/* 销毁二叉树*/

	void print(BSTNode* tree, int key, int direction);			/* 打印二叉树*/
};

#endif
