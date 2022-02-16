#ifndef CONTEST
#define CONTEST

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calc(const string &s, int i, int j, int cnt)
    {
        return 0;
    }

    // weekly contest 280
    int countOperations(int num1, int num2) {
        int res = 0;
        if (num1 < num2)
            swap(num1, num2);
        while (num2 != 0)
        {
            num1 -= num2;
            if (num1 < num2)
                swap(num1, num2);
            ++res;
        }
        return res;
    }

    int minimumOperations(vector<int>& nums) {
        vector<int> bucket1(100001), bucket2(100001);
        int res = 0;
        const int N = nums.size();
        for (int i = 0; i < N; ++i)
        {
            if (i % 2 == 0)
                ++bucket1[nums[i]];
            else
                ++bucket2[nums[i]];
        }
        int i = max_element(bucket1.begin(), bucket1.end()) - bucket1.begin();
        int j = max_element(bucket2.begin(), bucket2.end()) - bucket2.begin();
        if (i != j)
            res = N - bucket1[i] - bucket2[j];
        else
        {
            int tmp = bucket1[i];
            bucket1[i] = 0;
            res = N - *max_element(bucket1.begin(), bucket1.end()) - bucket2[j];
            bucket2[j] = 0;
            res = min(res, N - *max_element(bucket2.begin(), bucket2.end()) - tmp);
        }
        return res;
    }

    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(), beans.end());
        long long sum = 0;
        for (const int &val: beans)
            sum += val;
        const int N = beans.size();
        long long res = LONG_LONG_MAX;
        for (int i = 0; i < N; ++i)
            res = min(sum - (1ll * beans[i] * (N-i)), res);
        return res;
    }

    int maximumANDSum(vector<int>& nums, int numSlots) {
        const int N = nums.size();
        vector<vector<int>> a(numSlots+1, vector<int>(N));
        for (int i = 1; i < numSlots; ++i)
            for (int j = 0; j < N; ++j)
                a[i][j] = nums[j] & i;

    }
};

#endif