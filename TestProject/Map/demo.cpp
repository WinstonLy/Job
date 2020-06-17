#include "CMap.h"
#include <iostream>

using namespace std;

int main(void)
{
	CMap *pMap = new CMap(8);

	Node *pNodeA = new Node();
	pNodeA->m_cData = 'A';
	Node *pNodeB = new Node();
	pNodeB->m_cData = 'B';
	Node *pNodeC = new Node();
	pNodeC->m_cData = 'C';
	Node *pNodeD = new Node();
	pNodeD->m_cData = 'D';
	Node *pNodeE = new Node();
	pNodeE->m_cData = 'E';
	Node *pNodeF = new Node();
	pNodeF->m_cData = 'F';
	Node *pNodeG = new Node();
	pNodeG->m_cData = 'G';
	Node *pNodeH = new Node();
	pNodeH->m_cData = 'H';

	pMap->AddNode(pNodeA);
	pMap->AddNode(pNodeB);
	pMap->AddNode(pNodeC);
	pMap->AddNode(pNodeD);
	pMap->AddNode(pNodeE);
	pMap->AddNode(pNodeF);
	pMap->AddNode(pNodeG);
	pMap->AddNode(pNodeH);


	pMap->SetValueToMatrixForUndirectedGraph(0, 1, 1);
	pMap->SetValueToMatrixForUndirectedGraph(0, 3, 1);
	pMap->SetValueToMatrixForUndirectedGraph(1, 2, 1);
	pMap->SetValueToMatrixForUndirectedGraph(1, 5, 1);
	pMap->SetValueToMatrixForUndirectedGraph(3, 6, 1);
	pMap->SetValueToMatrixForUndirectedGraph(3, 7, 1);
	pMap->SetValueToMatrixForUndirectedGraph(6, 7, 1);
	pMap->SetValueToMatrixForUndirectedGraph(2, 4, 1);
	pMap->SetValueToMatrixForUndirectedGraph(4, 5, 1);

	pMap->PrintMatrix();


	return 0;
}