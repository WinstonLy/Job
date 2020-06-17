#include "CMap.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "string.h"

using namespace std;

CMap::CMap(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	Node *m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity*m_iCapacity];
	memset(m_pMatrix, 0, m_iCapacity*m_iCapacity*sizeof(int));

}
CMap::~CMap()
{
	delete []m_pNodeArray;
	delete []m_pMatrix;
}
bool CMap::AddNode(Node *pNode)
{
	if(pNode == NULL)
	{
		return false;
	}

	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}
void CMap::ResetNode()
{
	for(int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}
bool CMap::SetValueToMatrixForDirectedGraph(int row, int col, int val = 1)
{
	if(row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if(col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row*m_iCapacity + col] = val;
	return true;
}
bool CMap::SetValueToMatrixForUndirectedGraph(int row, int col, int val = 1)
{
	if(row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if(col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row*m_iCapacity + col] = val;
	m_pMatrix[col*m_iCapacity + row] = val;
	return true;
}
bool CMap::GetValueFromMatrix(int row, int col, int &val)
{
	if(row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if(col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	
	val = m_pMatrix[row * m_iCapacity + col];
	return true;
}
void CMap::PrintMatrix()
{
	for(int i = 0; i < m_iCapacity; i++)
	{
		for(int j = 0; j < m_iCapacity; j++)
		{
			cout << m_pMatrix[i * m_iCapacity + j] << " ";
		}
		cout << endl;
	}
	cout << "/************/" << endl;
}

void CMap::DepthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	for(int i = 0; i < m_iCapacity; i++)
	{
		GetValueFromMatrix(nodeIndex, i, value);
		if(value == 1)
		{
			if(m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else
			{
				DepthFirstTraverse(i);
			}
		}
		else
		{
			continue;
		}

	}
}
void CMap::BreadthFirstTraverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	vector<int> curVec;
	curVec.push_back(nodeIndex);

	BreadthFirstTraverseImpl(curVec); 
}
void CMap::BreadthFirstTraverseImpl(vector<int> preVec)
{
	int value = 0;
	vector<int> curVec;

	for(int j = 0; j < (int)preVec.size(); j++)
	{
		for(int i = 0; i < m_iCapacity; i++)
		{
			GetValueFromMatrix(preVec[j], i, value);
			if(value != 0)
			{
				if(m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;

					curVec.push_back(i);
				}
			}
		}
	}
}