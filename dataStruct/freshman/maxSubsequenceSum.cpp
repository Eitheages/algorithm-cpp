#include <bits/stdc++.h>
using namespace std;

/*
给定（可能是负的）整数序列A1,A2,...,AN,寻找(并标识)和最大的子序列。
如果所有整数都是负的，那么最大连续子序列的和是0.
*/
int maxSubsequenceSum(int a[], int size, int &start, int &end){
    start = 0;
    int max = 0, sum = 0;
    for (int i=0;i<size;++i){
        sum += a[i];
        if (sum>max){
            max = sum;
            end = i;
        }else if (sum<0){
            sum = 0;
            start = i+1;
        }
    }
    return max;
}

int main(){
    return 0;
}