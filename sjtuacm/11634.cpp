/*
给定1~n的任意排列，用堆排，快排或归并进行从小到大排序，输出比较次数。

要求如下：

堆排序：小根堆，建堆方式：
    1. 增加堆的长度，在末尾处插入元素。
    2. 比较当前元素和它的父结点值，如果小于父结点值，则交换，否则返回。
    3. 重复步骤2.
归并排序：区间等分（如果是奇数，左边比右边小1）
快速排序：以第一个元素为比较元
*/

#include <iostream>


int main(int argc, char **argv)
{
    int n, k, *nums;
    std::cin >> n >> k;
    nums = new int[n];
    for (register int i = 0; i < n; ++i)
        std::cin >> nums[i];
}