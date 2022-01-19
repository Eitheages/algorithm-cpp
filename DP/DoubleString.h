#ifndef DS
#define DS

#include <bits/stdc++.h>
using namespace std;

namespace C
{

class Solution
{
public:
    string longestPalindrome(string s) {
        const int N = s.length();
        string res = "";
        int maxlength = 0;
        for (int i = 0; i < N; i++)
        {
            int l, r;
            l = r = i;
            while (l > 0 && r < N-1 && s[l-1] == s[r+1])
            {
                l--;
                r++;
            }
            if (r-l+1 > maxlength)
            {
                maxlength = r-l+1;
                res = s.substr(l, maxlength);
            }
            if (i+1 < N && s[i] == s[i+1])
            {
                l = i;
                r = i+1;
                while (l > 0 && r < N-1 && s[l-1] == s[r+1])
                {
                    l--;
                    r++;
                }
                if (r-l+1 > maxlength)
                {
                    maxlength = r-l+1;
                    res = s.substr(l, maxlength);
                }
            }
        }
        return res;
    }

    int longestPalindromeSubseq(string s) {
        const int N = s.length();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        for (int i = N-1; i >= 0; i--)
        {
            dp[i][i] = 1;
            char s1 = s[i];
            for (int j = i+1; j < N; j++)
            {
                if (s1 == s[j])
                    dp[i][j] = dp[i+1][j-1] + 2;
                else
                    dp[i][j] = max(dp[i][j-1], dp[i+1][j]);
            }
        }
        return dp[0][N-1];
    }

    // string reverse(string s)
    // {
    //     const int N = s.length();
    //     for (register int i = 0; i < N/2; i++)
    //     {
    //         char tmp = s[i];
    //         s[i] = s[N-1-i];
    //         s[N-1-i] = tmp;
    //     }
    //     return s;
    // }

    // int longestPalindromeSubseq(string s)
    // {
    //     const int N = s.length();
    //     string ss = reverse(s);
    //     vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
    //     for (int i = 1; i <= N; i++)
    //     {
    //         for (int j = 1; j <= N; j++)
    //         {
    //             if (s[i-1] == ss[j-1])
    //                 dp[i][j] = dp[i-1][j-1] + 1;
    //             else
    //                 dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
    //         }
    //     }
    //     return dp[N][N];
    // }

};

}

#endif