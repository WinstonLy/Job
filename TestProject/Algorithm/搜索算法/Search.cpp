#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief  二分查找
 * @retval 成功返回下标，失败返回-1
 */

int BinarySearch(vector<int> v, int value , int low, int high)
{
    if(v.size() == 0)
        return -1;
    

    int mid = (low + high)/2;

    /* 迭代查找 */  
    while(low < high)
    {
        if(v[mid] == value)
        {
            return mid;
        }
        else if(v[mid] > value)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;

    /* 递归查找 */
    // if(v[mid] == value)
    //     return mid;
    // else if(v[mid] > value)
    //     return BinarySearch(v, value, low, mid-1);
    // else
    // {
    //     return BinarySearch(v, value, mid+1, high);
    // }
    
}





int main()
{
    int a[] = {2, 5, 6, 85, 56, 24, 10, 9, 32, 28};
    int b[] = {1, 3, 6, 10, 25, 36, 85, 96, 102, 250}; 
    vector<int> c;

    cout << "待查找列表:" << endl;
    for(int i = 0; i < 10; ++i)
    {
        c.push_back(b[i]);
    }

    for(auto &k : c)
        cout << k;
    cout << endl;
        
    cout << "二分查找结果" << BinarySearch(c, 25, 0, 8) << endl;
   


   

}
