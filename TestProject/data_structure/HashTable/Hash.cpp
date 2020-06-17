#include <iostream>
#include <limits.h>
#include "Hash.h"

using namespace std;


HashTable::HashTable(int _size)
{
	m_size = _size;
	m_use = 0;
	m_pdata = new int(m_size);
	for(int i = 0; i < m_size; ++i)
	{
		m_pdata[i] = INT_MIN;
	}
}	

HashTable::~HashTable()
{
	delete[] m_pdata;
}
	
bool HashTable::hash_full()
{
	return m_use>=m_size;
}

void HashTable::hash_insert(int new_data)
{
	if(hash_full())
	{
		cout << "hash table is full" << endl;
		return;
	}

	// 哈希函数实现方式为除留余数法
	int hash_index = new_data % m_size;
	if(m_pdata[hash_index] == INT_MIN)
	{
		m_pdata[hash_index] = new_data;
		++m_use;
		return;
	}

	// hash冲突解决办法是开放定址法，增量增长方式为线性探测法
	for(int index = 1; index < m_size; ++index)
	{
		hash_index = (new_data + index) % m_size;
		if(m_pdata[hash_index] == INT_MIN)
			break;
	}
	m_pdata[hash_index] = new_data;
	++m_use;

}
int HashTable::hash_find(int dst_data)
{
	int hash_index = dst_data % m_size;
	if(m_pdata[hash_index] == INT_MIN)
		return -1;
	if(m_pdata[hash_index] == dst_data)
		return hash_index;

	for(int index = 1; index < m_size; ++index)
	{
		hash_index = (dst_data + index) % m_size;
		if(m_pdata[hash_index] == INT_MIN)
			return -1;
		if(m_pdata[hash_index] == dst_data)
			return hash_index;
	}

	return -1;
}

void HashTable::hash_print()
{
	cout << "hash表中数据如下：";
	for(int index = 0; index < m_use; ++index)
	{
		cout << m_pdata[index] << " ";
	}
	cout << endl;
}

