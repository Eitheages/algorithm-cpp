#ifndef SOLU
#define SOLU

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 290. Word Pattern
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> mp1;
        unordered_map<string, char> mp2;

        s += ' ';
        int i = 0, j = 0, n = s.length();

        for (const char& ch : pattern) {
            // if s has been fully travelled, return true
            if (i >= n)
                return false;
            while (s[j++] != ' ')
                ;
            string tmp = s.substr(i, j - i - 1);
            i = j;

            if (mp1.count(ch) && mp1[ch] != tmp)
                return false;
            if (mp2.count(tmp) && mp2[tmp] != ch)
                return false;

            mp1[ch] = tmp;
            mp2[tmp] = ch;
        }
        // if s is not fully travelled, return false
        return i >= n;
    }

    // 187. Repeated DNA Sequence
    vector<string> findRepeatedDnaSequences(string s) {
        const int N = s.length();
        if (N <= 10)
            return {};
        unordered_map<string, int> mp;
        for (int i = 0; i <= N - 10; ++i) {
            string tmp = s.substr(i, 10);
            ++mp[tmp];
        }
        vector<string> res;
        for (auto it = mp.begin(), it_ = mp.end(); it != it_; ++it)
            if (it->second >= 2)
                res.push_back(it->first);
        return res;
    }

    // 5. Longest Palindromic Substring
    string longestPalindrome(string s) {
        const int N = s.length();
        int beginI = 0, endI = 0;
        vector<vector<bool>> dp(N, vector<bool>(N, 0));
        for (int j = 1; j < N; ++j) {
            for (int i = 0; i < j; ++i) {
                dp[i][j] = (s[i] == s[j]) && (j - i < 3 || dp[i + 1][j - 1]);
                if (dp[i][j] && j - i > endI - beginI) {
                    beginI = i;
                    endI = j;
                }
            }
        }
        return s.substr(beginI, endI - beginI + 1);
    }
};

#endif