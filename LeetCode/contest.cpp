#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calc(const string &s, int i, int j, int cnt)
    {
        if (cnt == 0)
            return 0;
        int times = 0;
        while (s[i] == '1')
        {
            ++i;
            --cnt;
            ++times;
        }
        while (s[j] == '1')
        {
            --j;
            --cnt;
            ++times;
        }
        int res_low = 1 + min(calc(s, i+1, j, cnt), calc(s, i, j-1, cnt));
        res_low = min(2*cnt, res_low);
        return times + res_low;
    }

    // int minimumTime(string s) {
    //     int cnt = 0;
    //     int n = s.length();
    //     for (const char &ch: s)
    //         if (ch == '1')
    //             ++cnt;
    //     int i = 0, j = n - 1;
    //     return calc(s, i, j, cnt);
    // }

    int minimumTime(string s) {
        int n = s.length();
        int res = 0;
        int i = 0, j = n - 1;
        while (1)
        {
            while (i <= j && s[i] == '1')
                ++i, ++res, --n;
            while (i <= j && s[j] == '1')
                --j, ++res, --n;
            if (i < j && s[i+1] == '1')
                i += 2, res += 2, n -= 2;
            if (i < j && s[j-1] == '1')
                j -= 2, res += 2, n -= 2;
        }
        if (i > j)
            return res;
        vector<int> dp(n+1);
        for (int k = 1; k <= n; ++k)
        {

        }

    }
};