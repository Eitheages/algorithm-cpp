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
};


#endif