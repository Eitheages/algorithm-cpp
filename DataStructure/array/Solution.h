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

};


#endif