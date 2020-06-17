/**
 * 八皇后问题描述：
 * 在8×8格的国际象棋上摆放八个皇后，使其不能互相攻击，即任意两个皇后都不能处于同一行、
 * 同一列或同一斜线上，问一共有多少种摆法。
 */

#include <iostream>
using namespace std;

bool is_ok(int c[], int row, int n);	// 判断能否在第 row 行第 c[row] 列插入一个皇后
void queen(int row, int c[], int n, int &total);	// 回溯算法的核心部分

int main()
{
	int n;	// 皇后的数量
	cout << "Please enter the number:\n";
	cin >> n;
	int* c = new int[n];	// 记录皇后的位置，如c[i]的值为j，表示第i行的皇后在第j列
	int total = 0;		// 记录解决方案的种数
	queen(0, c, n, total);
	cout << "The number of solution is: " << total << endl;

	return 0;
}

bool is_ok(int c[], int row, int n)
{
	for(int i = 0; i < row; ++i)
	{
		if(c[i] == c[row] || c[i] - i == c[row] - row || c[i] + i == c[row] + row)
			return false;
	}

	return true;
}

void queen(int row, int c[], int n, int &total)
{
	if(row == n)
	{
		for(int i = 0; i < n; ++i)
			cout << c[i] << " ";
		cout << endl;
		++total;
	}
	else
	{
		for(int col = 0; col < n; ++col)
		{
			c[row] = col;

			if(is_ok(c, row, n))
				queen(row+1, c, n, total);
		}	
	}
	
}
