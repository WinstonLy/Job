#ifndef _CMAP_H_
#define _CMAP_H_

#include <vector>
#include "Node.h"

using namespace std;

class CMap
{
public:
	CMap(int capacity);
	~CMap();
	bool AddNode(Node *pNode);
	void ResetNode();
	bool SetValueToMatrixForDirectedGraph(int row, int col, int val);
	bool SetValueToMatrixForUndirectedGraph(int row, int col, int val);
	bool GetValueFromMatrix(int row, int col, int &val);

	void PrintMatrix();
	void DepthFirstTraverse(int nodeIndex);
	void BreadthFirstTraverse(int nodeIndex);

private:
	void BreadthFirstTraverseImpl(vector<int> preVec);

private:
	int m_iCapacity;
	int m_iNodeCount;
	Node *m_pNodeArray;
	int *m_pMatrix;

};

#endif