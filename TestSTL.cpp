/***
 * @Author: liqunwu
 * @Date: 2023-10-11 17:13:57
 * @Description:
 * @Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <vector>
#include <set>

using namespace std;

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int PartSort1(int data[], int left, int right)
{
    int keyi = left;
    while (left < right)
    {
        while (data[right] >= data[keyi] && left < right)
        {
            right--;
        }

        while (data[left] <= data[keyi] && left < right)
        {
            left++;
        }

        // 交换
        Swap(&data[right], &data[left]);
    }

    // 交换
    Swap(&data[left], &data[keyi]);

    return left;
}

void QuickSort(int data[], int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int left = begin, right = end;
    int key = PartSort1(data, left, right);
    QuickSort(data, begin, key - 1);
    QuickSort(data, key + 1, end);
}

int main()
{
    int data[] = {3, 1, 5, 7, 3};

//3, 1, 5, 7, 3
    QuickSort(data, 0, 4);

    for (int i = 0; i < 5; i++)
    {
        cout << data[i] << " ";
    }

    cout << endl;
}