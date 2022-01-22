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

    bool isSubsequence(string s, string t)
    {
        const int N = t.length();
        vector<vector<int>> dp(N+1, vector<int>(26));
        for (int i = N; i >= 0; --i)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (i == N)
                {
                    dp[i][j] = N;
                    continue;
                }
                if (t[i] == j + 'a')
                    dp[i][j] = i;
                else
                    dp[i][j] = dp[i+1][j];
            }
        }
        int p1 = 0, p2 = 0;
        while (p1 < s.length())
        {
            p2 = dp[p2][s[p1++] - 'a'] + 1;
            if (p2 == N + 1)
                return 0;
        }
        return 1;
    }

    int longestCommonSubsequence(string text1, string text2) {
        const int M = text1.length();
        const int N = text2.length();
        vector<vector<int>> dp(M+1, vector<int>(N+1));
        for (int i = 1; i <= M; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[M][N];
    }

    int minDistance(string word1, string word2) {
        const int M = word1.length(), N = word2.length();
        vector<vector<int>> dp(M+1, vector<int>(N+1));
        for (int i = 0; i <= M; ++i)
        {
            if (i == 0)
            {
                for (int j = 0; j <= N; ++j)
                    dp[i][j] = j;
                continue;
            }
            dp[i][0] = i;
            for (int j = 1; j <= N; ++j)
            {
                if (word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]));
            }
        }
        return dp[M][N];
    }

    int change(int amount, vector<int>& coins) {
        const int N = coins.size();
        vector<vector<int>> dp(N, vector<int>(amount+1, 0));
        int tmp = coins.front();
        for (int j = 0; j <= amount; ++j)
            dp[0][j] = j % tmp == 0? 1: 0;
        for (int i = 1; i < N; ++i)
        {
            dp[i][0] = 1;
            for (int j = 1; j <= amount; ++j)
            {
                dp[i][j] += dp[i-1][j];
                if (j - coins[i] >= 0)
                    dp[i][j] += dp[i][j-coins[i]];
            }
        }
        return dp[N-1][amount];
    }
};

}

#endif