#include <iostream>
#include "list.cpp"

using namespace std;

int main()
{
	int a[5] = {1, 5, 6, 2, 7};

	
	List<int> *list = new List<int>(6);


	if(list->listEmpty())
		cout << "list is empty" << endl;

	/** 构建线性表 list */
	list->listInsertHead(a[0]);
	list->listInsert(1, a[1]);

	// cout << "list 长度" << list->getListLength() << endl;
	
	list->listInsert(2, a[2]);
	list->listInsertHead(a[3]);
	list->listInsert(4, a[4]);

 	cout << "list 遍历结果如下：" << endl;
	list->listTraverse();
	
	int i = 2;
	int m = 0;
	cout << "删除元素结果如下：" << endl;
	list->listDelete(i, m);
	cout << m << endl;
	cout << "删除之后遍历结果如下：" << endl;
	list->listTraverse();

	// int b = 6;
	// int m = 0;
	// cout << "查找前驱结果如下：" << endl;
	// list->priorElem(b, m);
	// cout << b << "的前驱是： " << m << endl;
	// cout << "查找后继结果如下：" << endl;
	// list->nextElem(b, m);
	// cout << b << "的后继是： " << m << endl;
	// 
	// int b = 7;
	// cout << "查找元素结果如下：" << endl;
	// cout << list->locateElem(b) << endl;

	// cout << "查找下标结果如下：" << endl;
	// int value = 0;
	// list->getElem(2, value);
	// cout << value << endl;

	// cout << "list 长度" << list->getListLength() << endl;
	
	// list->clearList();
	// if(list->listEmpty())
	// 	cout << "list is empty" << endl;

	// cout << "list 遍历结果如下：" << endl;
	// list->listTraverse();

	delete list;
	list = NULL;

	return 0;
}