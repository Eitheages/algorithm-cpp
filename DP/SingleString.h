#ifndef SS
#define SS

#include <bits/stdc++.h>
using namespace std;

namespace A
{
class Solution
{
public:
    template <class T>
    T threeMin(T a, T b, T c)
    {
        T tmp = a > b ? b : a;
        return tmp > c ? c : tmp;
    }

    template <class T>
    T threeMax(T a, T b, T c)
    {
        T tmp = a < b ? b : a;
        return tmp < c ? c : tmp;
    }

    int minSwap(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> a = {1};
        vector<int> b = {0};
        int n = min(nums1.size(), nums2.size());
        for (int i = 1; i < n; i++)
        {
            a.emplace_back(INT_MAX);
            b.emplace_back(INT_MAX);
            if (nums1[i - 1] < nums1[i] && nums2[i - 1] < nums2[i])
            {
                a[i] = min(a[i - 1] + 1, a[i]);
                b[i] = min(b[i - 1], b[i]);
            }
            if (nums1[i - 1] < nums2[i] && nums2[i - 1] < nums1[i])
            {
                a[i] = min(b[i - 1] + 1, a[i]);
                b[i] = min(a[i - 1], b[i]);
            }
        }
        int res = min(a[n - 1], b[n - 1]);
        return res;
    }

    int numTilings(int n)
    {
        vector<long long int> dp = {1, 0, 0, 0}, ndp = dp;
        const long long int MOD = 1000000007;
        while (n--)
        {
            ndp[0] = (dp[0] + dp[3]) % MOD;
            ndp[1] = (dp[0] + dp[2]) % MOD;
            ndp[2] = (dp[0] + dp[1]) % MOD;
            ndp[3] = (dp[0] + dp[1] + dp[2]) % MOD;
            dp = ndp;
        }
        return dp[0];
    }

    int findNumberOfLIS(vector<int> &nums)
    {
        vector<int> dp = {1}, cnt = {1};
        for (int i = 1; i < nums.size(); ++i)
        {
            dp.emplace_back(1);
            cnt.emplace_back(1);
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                {
                    if (dp[i] < dp[j] + 1)
                    {
                        dp[i] = dp[j] + 1;
                        cnt[i] = 0;
                    }
                    if (dp[i] == dp[j] + 1)
                        cnt[i] += cnt[j];
                }
        }
        int res(0), max(0);
        for (int i = 0; i < nums.size(); i++)
        {
            if (max < dp[i])
            {
                max = dp[i];
                res = 0;
            }
            if (max == dp[i])
                res += cnt[i];
        }
        return res;
    }

    int maxEnvelopes(vector<vector<int>> &envelopes)
    {
        sort(
            envelopes.begin(), envelopes.end(),
            [](const vector<int> &enve1, const vector<int> &enve2) -> bool
            {
                if (enve1[0] < enve2[0])
                    return true;
                if (enve1[0] == enve2[0] && enve1[1] < enve2[1])
                    return true;
                else
                    return false;
            });
        vector<int> dp;
        for (int i = 0; i < envelopes.size(); i++)
        {
            dp.emplace_back(1);
            for (int j = 0; j < i; j++)
            {
                if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
                {
                    int temp = dp[j] + 1;
                    dp[i] = max(dp[i], temp);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    int maxSubarraySumCircular(vector<int> &nums)
    {
        int temp1(0), res(INT_MIN);
        int min_sum(INT_MAX), sum(0), temp2(0);
        for (const int &val : nums)
        {
            temp1 = max(temp1 + val, val);
            res = max(res, temp1);
            temp2 = min(temp2 + val, val);
            min_sum = min(temp2, min_sum);
            sum += val;
        }
        return res > 0 ? max(res, sum - min_sum) : res;
    }

    int maxSumSubmatrix(vector<vector<int>> &matrix, int k)
    {
        int res(INT_MIN);
        int m(matrix.size()), n(matrix[0].size());
        for (int i = 0; i < m; i++)
        {
            vector<int> dp(n);
            for (int j = i; j < m; j++)
            {
                for (int c = 0; c < n; c++)
                {
                    dp[c] += matrix[j][c];
                }
                //补充定义第一个前缀和是0，因为只选取第一列也有可能是答案
                //幸好只需要返回最小的和，不用返回子式的具体位置
                vector<int> sums = {0};
                int s(0);
                for (const int &val : dp)
                {
                    //计算遍历前缀和
                    s += val;
                    int l(0), r(sums.size());
                    //在sums中找到第一个大于等于s-k的数的下标，如果没有，返回sums.size()
                    while (l < r)
                    {
                        int m = (l + r) >> 1;
                        if (sums[m] >= s - k)
                            r = m;
                        else
                            l = m + 1;
                    }
                    if (r != sums.size())
                        res = max(res, s - sums[r]);
                    // 维护sums为一个递增数列
                    l = 0;
                    r = sums.size();
                    while (l < r)
                    {
                        int m = (l + r) >> 1;
                        if (sums[m] >= s)
                            r = m;
                        else
                            l = m + 1;
                    }
                    sums.insert(sums.begin() + r, s);
                }
            }
        }
        return res;
    }

    int rob(vector<int> &nums)
    {
        vector<int> dp = {0, 0, nums[0]};
        for (auto it = nums.begin() + 1; it != nums.end(); it++)
        {
            int temp = max(dp[0], dp[1]) + *it;
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = temp;
        }
        return max(dp[1], dp[2]);
    }

    int deleteAndEarn(vector<int> &nums)
    {
        const int N = int(1e4);
        vector<int> bucket(N + 1);
        for (const int &val : nums)
            bucket[val]++;
        int p = 0, q = 0;
        for (int i = 1; i <= N; i++)
        {
            int temp = max(p + i * bucket[i], q);
            p = q;
            q = temp;
        }
        return max(p, q);
    }

    bool canJump(vector<int> &nums)
    {
        auto p = nums.end() - 1, q = p;
        while ((q--) != nums.begin())
        {
            if (p - q <= *q)
                p = q;
        }
        return (p == nums.begin());
    }

    /* A Time Exceeded answer
    int jump(vector<int>& nums) {
        const int N = nums.size();
        vector<int> dp(N);
        dp[0] = 0;
        for (int i = 1; i < N; i++)
        {
            dp[i] = INT_MAX;
            for (int j = 0; j < i; j++)
                if (j + nums[j] >= i)
                    dp[i] = min(dp[i], dp[j] + 1);
        }
        return dp[N - 1];
    }*/

    int jump(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 0;
        int res = 0;
        int l = 0, r = 0, rm = r;
        for (; l < nums.size(); l++)
        {
            rm = max(l + nums[l], rm);
            if (l == r)
            {
                r = max(rm, nums[r] + r);
                res++;
                if (r >= nums.size() - 1)
                    break;
            }
        }
        return res;
    }

    // struct Status
    // {
    //     int neg_cnt, l_length, r_length, length, result;
    // };

    // Status pushup(const Status &l, const Status &r)
    // {
    //     int neg_cnt = l.neg_cnt + r.neg_cnt;
    //     int l_length = r.neg_cnt == 0? l.l_length: l.length + r.l_length;
    //     int r_length = l.neg_cnt == 0? r.r_length: l.r_length + r.length;
    //     int length = l.length + r.length;
    //     int result = neg_cnt%2==0? length: max(l_length, r_length);
    //     return (Status){neg_cnt, l_length, r_length, length, result};
    // }

    // Status get(vector<int> &nums, int l, int r)
    // {
    //     if (l == r)
    //     {
    //         int neg_cnt = nums[l] > 0? 0: 1;
    //         int result = (neg_cnt + 1) % 2;
    //         return (Status){neg_cnt, 0, 0, 1, result};
    //     }
    //     int m = (l + r) >> 1;
    //     return pushup(get(nums, l, m), get(nums, m+1, r));
    // }

    // int getMaxLen(vector<int>& nums) {
    //     int res = 0;
    //     int i = 0;
    //     while (nums[i] == 0)
    //         if (++i == nums.size())
    //             return res;
    //     int j = i;
    //     for (;j < nums.size(); j++)
    //     {
    //         if (nums[j] == 0)
    //         {
    //             res = max(get(nums, i, j-1).result, res);
    //             i = j + 1;
    //             while (nums[i] == 0)
    //                 if (++i == nums.size())
    //                     return res;
    //             j = i;
    //         }
    //     }
    //     res = max(get(nums, i, j-1).result, res);
    //     return res;
    // }

    int maxScoreSightseeingPair(const vector<int> &values)
    {
        int res = INT_MIN;
        int cur = 0;
        for (const int &val : values)
        {
            res = max(res, cur + val - 1);
            cur = max(cur - 1, val);
        }
        return res;
    }

    int maxProfit1(vector<int> &prices)
    {
        int res = 0, cur = INT_MAX;
        for (const int &price : prices)
        {
            res = max(res, price - cur);
            cur = min(cur, price);
        }
        return res;
    }

    int maxProfit2(vector<int> &prices)
    {
        int pre = prices[0], res = 0;
        for (const int &price : prices)
        {
            if (price > pre)
                res += price - pre;
            pre = price;
        }
        return res;
    }

    // int maxProfit3(vector<int>& prices)
    // {
    //     int profit = 0; // record the total profit
    //     int l = 0, r = 0;
    //     for (int i = 1; i < prices.size(); i++)
    //     {
    //         if (prices[i] >= prices[i-1])
    //             r = i;
    //         else
    //         {
    //             int j = i;
    //             while (i < prices.size() && prices[i] <= prices[i-1])
    //                 i++;
    //             if (i == prices.size())
    //                 break;
    //             if (i-j >= 2)
    //             {
    //                 profit += prices[r] - prices[l];
    //                 l = i - 1;
    //                 r = i;
    //             }
    //             else
    //             {
    //                 if (r != l)
    //                 {
    //                     if (prices[j-2] < prices[j] && prices[j-1] < prices[i])
    //                         r = i;
    //                     else if (prices[j-1] - prices[j-2] < prices[i] - prices[j])
    //                     {
    //                         profit += prices[j-2] - prices[l];
    //                         l = j;
    //                         r = i;
    //                     }
    //                     else
    //                     {
    //                         profit += prices[j-1] - prices[l];
    //                         r = l = i;
    //                     }
    //                 }
    //                 else
    //                 {
    //                     l = j;
    //                     r = i;
    //                 }
    //             }
    //         }
    //     }
    //     profit += prices[r] - prices[l];
    //     return profit;
    // }

    int numberOfArithmeticSlices(vector<int> &nums)
    {
        if (nums.size() < 3)
            return 0;
        int dp = 0, res = 0;
        for (int i = 2; i < nums.size(); i++)
        {
            if (dp > 0 && 2 * nums[i - 1] == nums[i - 2] + nums[i])
                dp++;
            else if (2 * nums[i - 1] == nums[i - 2] + nums[i])
                dp = 1;
            else
                dp = 0;
            res += dp;
        }
        return res;
    }

    int numDecodings(string s)
    {
        int dp1 = s[0] == '0' ? 0 : 1, dp2 = 0, t = dp1 + dp2;
        for (int i = 1; i < s.length(); i++)
        {
            if (dp1 + dp2 == 0)
                break;
            if (s[i] > '0')
                t = dp1 + dp2;
            else
                t = 0;
            if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6')
                dp2 = dp1;
            else
                dp2 = 0;
            dp1 = t;
        }
        return dp1 + dp2;
    }

    int nthUglyNumber(int n)
    {
        vector<int> dp(n, 1);
        int p2 = 0, p3 = 0, p5 = 0;
        for (int i = 1; i < n; i++)
        {
            int num1 = dp[p2] * 2, num2 = dp[p3] * 3, num3 = dp[p5] * 5;
            dp[i] = threeMin<int>(num1, num2, num3);
            if (dp[i] == num1)
                p2++;
            if (dp[i] == num2)
                p3++;
            if (dp[i] == num3)
                p5++;
        }
        return dp[n - 1];
    }

    int lengthOfLIS(vector<int>& nums) {
        const int N = nums.size();
        vector<int> dp(N, 1);
        for (int i = 1; i < N; i++)
            for (int j = 0; j < i; j++)
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j]+1);
        return *max_element(dp.begin(), dp.end());
    }

    int wiggleMaxLength(vector<int>& nums) {
        const int N = nums.size();
        vector<int> dp(N, 1);
        //1: the next difference shoule be positive; -1: negtive; 0: both are ok
        vector<short> state(N, 0);
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] == nums[i])
                    continue;
                if (state[j] == 0 || state[j] == 1 && nums[j] < nums[i] || state[j] == -1 && nums[j] > nums[i])
                {
                    if (dp[j]+1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        state[i] = (nums[j] > nums[i])? 1: -1;
                    }
                    else if (dp[j]+1 == dp[i])
                    {
                        if (state[i] == 1 && nums[j] < nums[i] || state[i] == -1 && nums[j] > nums[i])
                            state[i] == 0;
                    }
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

}

#endif