/**
 * about: 	建立哈希表，实现哈希查找，插入等
 * by：		Winston
 * time：	2020.6.12
 */

#ifndef __HASH_H__
#define __HASH_H__

class HashTable
{
public:
	HashTable(int _size);	
	~HashTable();
	
	bool hash_full();
	void hash_insert(int new_data);
	int hash_find(int dst_data);
	void hash_print();

private:
	int m_size;		// 总大小
	int m_use;		// 已使用大小
	int *m_pdata;

};

#endif