//#include <stdlib.h>
#include <iostream>

#include "List.h"

using namespace std;

int main(void)
{
	// 1 2 3 4 5
	Coordinate e1(3,5);
	Coordinate e2(6,7);
	Coordinate e3(4,1);

	/* int e2 = 2;
	int e3 = 3;

	int e4 = 4;
	int e5 = 5; */

	Coordinate temp(0,0);
	CList *list1 = new CList(10);
	
	cout << "Length" << list1->ListLength() << endl;

	list1->ListInsert(0, &e1);
	list1->ListInsert(1, &e2);
	list1->ListInsert(1, &e3);
	// list1->ListInsert(3, &e4);
	// list1->ListInsert(2, &e5);

	cout << "Length" << list1->ListLength() << endl;
	// int temp = 0;
	list1->ListTraverse();

	list1->ListDelete(1,&temp);
	cout << "delete " << temp << endl;

	if(!list1->ListEmpty())
	{
		cout << "not empty" << endl;
	}

	/* list1->ClearList();
	if(list1->ListEmpty())
	{
		cout << "is empty" << endl;
	}  */

	list1->ListTraverse();

	// int temp = 0;
	list1->GetElem(0, &temp);
	cout << "temp " << temp << endl;

	cout << "temp locate" << list1->LocateElem(&temp) << endl;

	if(!list1->PriorElem(&e2, &temp))
	{
		cout << "not have prior" << endl;
	}
	else
	{
		cout << "temp prior " << temp << endl;
	}

	if(!list1->NextElem(&e1, &temp))
	{
		cout << "not have next " << endl;
	}
	else
	{
		cout << "temp next " << temp << endl;
	} 

	delete []list1;
}