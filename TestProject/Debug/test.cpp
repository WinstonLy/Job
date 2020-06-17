#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <malloc.h>  
#include <string.h>  
using namespace std;

void func()
{
	int *x = (int *)malloc(10 * sizeof(int ));
	x[10] = 0;
}

int sum(int n)
{
    int ret = 0;

    if( n > 0 )
    {
        ret = n + sum(n-1);
    }

    return ret;
}



void test()  
{  
    int *ptr = (int*)malloc(sizeof(int)*10);  
  
    ptr[10] = 7; // 内存越界  
  
    memcpy(ptr +1, ptr, 5); // 踩内存  
  
  
    // free(ptr);   
    // free(ptr);// 重复释放  
  
    int *p1;  
    *p1 = 1; // 非法指针  
}  
  
int main(void)  
{  
    int s[5];
    cout << s[5] << endl;
    test();  

    return 0;  
}  