#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int menu()
{
	// 显示通讯录功能菜单
	cout << "功能菜单" << endl;
	cout << "1. 新建联系人" << endl;
	cout << "2. 删除联系人" << endl;
	cout << "3. 浏览通讯录" << endl;
	cout << "4. 退出通讯录" << endl;

	cout << "请输入: ";

	int order = 0;

	cin >> order;
	return order;
}

void CreatPerson(List *pList)
{
	Node node;
	Person person;
	
	cout << "请输入名字: ";
	cin >> person.m_strName;
	cout << "请输入电话号码： ";
	cin >> person.m_strPhone;
	node.data = person;
	pList->ListInsertTail(&node);
}

void DeletePerson(List *pList)
{
	// string tempName;
	int tempLocation;

	Node node;
	cout << "请输入要删除的联系人序号： ";
	cin >> tempLocation;
	pList->ListDelete(tempLocation, &node);
	cout << "成功删除联系人： " << node.data.m_strName << endl;

}
int main(void)
{
	int userOrder = 0;
	List *pList = new List();

	while(userOrder != 4)
	{
		userOrder = menu();
		switch(userOrder)
		{
			case 1:
				cout << "用户指令---->新建联系人: " << endl;
				CreatPerson(pList);
				break;
			case 2:
				cout << "用户指令---->删除联系人: " << endl;
				DeletePerson(pList);
				break;
			case 3:
				cout << "用户指令---->浏览通讯录: " << endl;
				pList->ListTraverse();
				break;
			case 4:
				cout << "用户指令---->退出通讯录: " << endl;
				break;
			default:
				break;
		}
	}

	delete pList;
	pList = NULL;

	return 0;
}