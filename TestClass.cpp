/***
 * @Author: liqunwu
 * @Date: 2023-10-11 16:00:26
 * @Description:
 * @Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */
#include <iostream>
using namespace std;

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int PartSort1(int *arr, int left, int right)
{
    int keyi = left;
    while (left < right)
    {
        // 从右找小
        while (left < right && arr[right] >= arr[keyi])
        {
            right--;
        }
        // 从左找大
        while (left < right && arr[left] <= arr[keyi])
        {
            left++;
        }
        // 交换
        Swap(&arr[right], &arr[left]);
    }
    // 循环结束后，交换最后一次，交换最左侧的key值与左右指针同时指向的值
    Swap(&arr[left], &arr[keyi]);
    keyi = left;

    return keyi;
}

// 递归
void QuickSort(int *arr, int begin, int end)
{
    // 只有一个节点
    if (begin >= end)
    {
        return;
    }
    int left = begin, right = end;
    // 三种方法
    int key = PartSort1(arr, left, right); // 左右交换法
                                           // PartSort2(arr, left, right);//挖坑法
                                           //  PartSort3(arr, left, right);//前后指针法
    //[begin,key-1]
    QuickSort(arr, begin, key - 1);
    //[key+1,end]
    QuickSort(arr, key + 1, end);
}

int main()
{
    int data[] = {3, 1, 5, 7, 3};

    QuickSort(data, 0, 4);

    for (int i = 0; i < 5; i++)
    {
        cout << data[i] << " ";
    }

    cout << endl;
}