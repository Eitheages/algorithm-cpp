// 经典题 寻找最长上升子序列
#ifndef CLASSIC
#define CLASSIC

#include <bits/stdc++.h>
using namespace std;

class Classic
{
    // 贪心 二分查找
public:
    int lengthOfLIS1(vector<int> &nums)
    {
        vector<int> temp = {nums[0]};
        int key, l, r;
        for (auto it = nums.begin() + 1; it != nums.end(); it++)
        {
            key = *it;
            l = 0;
            r = temp.size();
            while (l < r)
            {
                int m = (l + r) / 2;
                if (temp[m] >= key)
                    r = m;
                else
                    l = m + 1;
            }
            if (l == temp.size())
                temp.emplace_back(key);
            else
                temp[l] = key;
        }
        return temp.size();
    }

    // 动态规划
    int lengthOfLIS2(vector<int> &nums)
    {
        vector<int> dp = {1};
        for (int i=1;i<nums.size();i++)
        {
            dp.emplace_back(1);
            for (int j=0;j<i;++j)
                if (nums[j]<nums[i]&&dp[j]+1>dp[i])
                    dp[i] = dp[j]+1;
        }
        int res = dp[0];
        for (auto it = dp.begin();it!=dp.end();it++)
        {
            if (res<*it)
                res = *it;
        }
        return res;
    }
};

#endif