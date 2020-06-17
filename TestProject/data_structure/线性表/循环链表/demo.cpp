#include <iostream>
#include "Cyclelist.h"
#include "Node.h"

using namespace std;

int main()
{
	Cyclelist* list = new Cyclelist;
	list->initList(5);
	list->findAndKillK(3, 2);

	delete list;
	list = NULL;

	return 0;
}