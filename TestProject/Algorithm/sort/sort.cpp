/**
 * about 各种排序算法的实现
 * version 20200612 by Winston
 */


#include <iostream>
#include <vector>
using namespace std;
/**
 * 交换函数
 * @param a 
 * @param b 
 */
void swap(int& a, int& b)
{
	int temp = a;
	a = b; 
	b = temp;
}
/**
 * 插入排序实现,递增排序
 * @param vec 待排序数组
 */
void insert_sort(vector<int>& vec)
{
	for(int i = 0; i < vec.size() - 1; ++i)
	{
		for(int j = i + 1; j > 0; --j)
		{
			if(vec[j] < vec[j - 1])
				swap(vec[j], vec[j - 1]);
		}
	}
}

/**
 * 希尔排序
 */
void insert_sort_shell(vector<int>& vec, int gap, int index)
{
	int temp = vec[index];
	int i = 0;

	for(i = index - gap; i >= 0 && temp < vec[i]; i -= gap)
	{
			vec[i+gap] = vec[i];
	}
	vec[i + gap] = temp;

}
void shell_sort(vector<int>& vec)
{
	int N = vec.size();
	for(int gap = N /2; gap > 0; gap /= 2)
	{
		for(int i = gap; i < N; ++i)
		{
			insert_sort_shell(vec, gap, i);
		}
	}
}
int main()
{
	vector<int> vec;
	int a[7] = {5,3,9,12,1,65,35};
	for(int i = 0; i < 7; ++i)
	{
		vec.push_back(a[i]);
	}

	cout << "before sort" << endl;
	for(int i = 0; i < 7; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
 	
 	// 测试插入排序
	// insert_sort(vec);

	// 测试希尔排序
	shell_sort(vec);
	cout << "after sort :" << endl;
	for(int i = 0; i < 7; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

}