#ifndef SOLU
#define SOLU

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
    {
        sort(nums1.begin(), nums1.end()), sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        const int N = nums1.size(), M = nums2.size();
        vector<int> res;
        while (i < N && j < M)
        {
            if (nums1[i] == nums2[j])
                res.emplace_back(nums1[i]), ++i, ++j;
            else if (nums1[i] < nums2[j])
                ++i;
            else
                ++j;
        }
        return res;
    }

    void quicksort(const vector<int> &nums, vector<int> &p, int l, int r)
    {
        if (l >= r)
            return;
        int pivot = nums[p[r]];
        int i = l - 1, tmp;
        for (int j = l; j < r; ++j)
        {
            if (nums[p[j]] < pivot)
            {
                ++i;
                tmp = p[j];
                p[j] = p[i];
                p[i] = tmp;
            }
        }
        ++i;
        tmp = p[i];
        p[i] = p[r];
        p[r] = tmp;
        quicksort(nums, p, l, i-1);
        quicksort(nums, p, i+1, r);
    }

    int search(const vector<int> &nums, const vector<int> &p, int key)
    {
        int i = 0, j = nums.size()-1, m;

        while (i <= j)
        {
            m = (i + j) >> 1;
            if (nums[p[m]] == key)
                return m;
            else if (nums[p[m]] > key)
                j = m - 1;
            else
                i = m + 1;
        }
        return -1;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        const int N = nums.size();
        vector<int> p(N);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        quicksort(nums, p, 0, N-1);
        int index, key;
        for (int i = 0; i < N; ++i)
        {
            key = target - nums[p[i]];
            if ((key << 1) == target)
                if (nums[p[i]] == nums[p[i+1]])
                    return {p[i], p[i+1]};
                else
                    continue;
            index = search(nums, p, key);
            if (index != -1)
                return {p[i], p[index]};
        }
        return {0, 0};
    }

    // 53. Merge Intervals
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
                [](const vector<int> &a, const vector<int> &b)->bool{return (a[0] < b[0]);});
        vector<vector<int>> res;
        int begin = intervals[0][0], end = intervals[0][1];
        const int N = intervals.size();
        for (int i = 1; i < N; ++i)
        {
            if (end >= intervals[i][0])
                end = max(intervals[i][1], end);
            else
            {
                res.emplace_back(vector<int>{begin, end});
                begin = intervals[i][0];
                end = intervals[i][1];
            }
        }
        res.emplace_back(vector<int>{begin, end});
        return res;
    }

    // 240. Search a 2D Matrix II
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        const int M = matrix.size(), N = matrix[0].size();
        int j = N - 1, i = 0;
        while (i < M && j < N)
        {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] < target)
                ++i;
            else
                --j;
        }
        return false;
    }

    // 435. Non-overlapping Intervals
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(),
            [](vector<int> &a, vector<int> &b){return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];});
        const int N = intervals.size();
        vector<int> dp(N, 0);
        dp[0] = 1;
        for (int i = 1; i < N; ++i)
        {
            for (int j = 0; j < i; ++j)
                if (intervals[j][1] <= intervals[i][0])
                    dp[i] = max(dp[i], dp[j] + 1);
        }
        return N - *max_element(dp.begin(), dp.end());
    }
};


#endif