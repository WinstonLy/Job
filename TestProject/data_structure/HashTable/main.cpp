#include <iostream>
#include "Hash.h"
#include <string>

using namespace std;

int main()
{
	HashTable hashTable(5);

	while(true)
	{
		cout << "请输入操作：INSERT(1) FIND(2) PRINT(3) QUIT(4): " << endl;
		int choice;
		cin >> choice;
		if(choice == 4)
			break;
		switch(choice)
		{
			case 1:
				if(hashTable.hash_full())
					cout << "没有足够的剩余空间" << endl;
				else
				{
					cout << "请输入要插入的数据：";
					int new_data;
					cin >> new_data;
					hashTable.hash_insert(new_data);
				}

				break;
			case 2:
				cout << "请输入要查找的数据: ";
				int dst_data;
				cin >> dst_data;
				cout << "dst_data_index = " << hashTable.hash_find(dst_data) << endl;
				break;

			case 3:
				hashTable.hash_print();
				break;
			default:
				break;
		}
	}

	return 0;
}