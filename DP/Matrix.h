#ifndef MAT
#define MAT

#include <bits/stdc++.h>
using namespace std;


namespace B
{
class NumMatrix {
private:
    const int M, N;
    vector<vector<int>> subsum;
public:
    NumMatrix(vector<vector<int>>& matrix): M(matrix.size()), N(matrix[0].size())
    {
        subsum = vector<vector<int>>(M+1, vector<int>(N+1, 0));
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                subsum[i+1][j+1] = matrix[i][j] + subsum[i+1][j] + subsum[i][j+1] - subsum[i][j];
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return subsum[row2+1][col2+1]-subsum[row2+1][col1]-subsum[row1][col2+1]+subsum[row1][col1];
    }
};

class Solution
{
public:
    vector<int> getMaxMatrix(vector<vector<int>> &matrix)
    {
        vector<int> dp(matrix[0].size());
        vector<int> res;
        int temp(0), max_sum(INT_MIN);
        for (int i = 0; i < matrix.size(); i++)
        {
            // memset(&(*dp.begin()), 0, sizeof(dp));
            for (int &val : dp)
                val = 0;
            for (int j = i; j < matrix.size(); j++)
            {
                int r1(i), c1(0), r2(j), c2(0);
                for (int k = 0; k < matrix[0].size(); k++)
                {
                    dp[k] = dp[k] + matrix[j][k];
                    if (temp <= 0)
                    {
                        temp = dp[k];
                        c1 = k;
                    }
                    else
                    {
                        temp += dp[k];
                    }
                    if (temp > max_sum)
                    {
                        max_sum = temp;
                        c2 = k;
                        res = {r1, c1, r2, c2};
                    }
                }
                temp = 0;
            }
        }
        return res;
    }

    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        const int N = matrix.size();
        vector<int> dp(matrix[0]);
        for (int i = 1; i < N; i++)
        {
            vector<int> tmp(dp);
            dp[0] = min(tmp[0], tmp[1]) + matrix[i][0];
            dp[N - 1] = min(tmp[N - 2], tmp[N - 1]) + matrix[i][N - 1];
            for (int j = 1; j < N - 1; j++)
                dp[j] = min(min(tmp[j - 1], tmp[j]), tmp[j + 1]) + matrix[i][j];
        }
        int res = *min_element(dp.begin(), dp.end());
        return res;
    }

    int minimumTotal(vector<vector<int>> &triangle)
    {
        const int N = triangle.size();
        vector<int> dp(N);
        dp[0] = triangle[0][0];
        for (int i = 1; i < N; i++)
        {
            vector<int> tmp(dp);
            dp[0] = tmp[0] + triangle[i][0];
            dp[i] = tmp[i - 1] + triangle[i][i];
            for (int j = 1; j < i; j++)
                dp[j] = min(tmp[j - 1], tmp[j]) + triangle[i][j];
        }
        return *min_element(dp.begin(), dp.end());
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        const int M = mat.size();
        const int N = mat[0].size();
        vector<vector<int>> res(M, vector<int>(N, 0));
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int x1 = max(0, i - k);
                int y1 = max(0, j - k);
                int x2 = min(M, i + k + 1);
                int y2 = min(N, j + k + 1);
                while (x1 != x2)
                {
                    for (int c = y1; c < y2; c++)
                        res[i][j] += mat[x1][c];
                    x1++;
                }
            }
        }
        return res;
    }

    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++)
        {
            vector<int> tmp(dp);
            dp[0] = 1;
            for (int j = 1; j < n; j++)
                dp[j] = dp[j-1] + tmp[j];
        }
        return dp[n-1];
    }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> &mat = obstacleGrid;
        const int M = mat.size(), N = mat[0].size();
        vector<int> dp(N, 0);
        dp[0] = (mat[0][0] == 0);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (mat[i][j] == 1)
                    dp[j] = 0;
                else if (j > 0 && mat[i][j-1] == 0 )
                    dp[j] += dp[j-1];
            }
        }
        return dp.back();
    }

    int minPathSum(vector<vector<int>>& grid) {
        const int M = grid.size(), N = grid[0].size();
        vector<int> dp(N, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < M; i++)
        {
            dp[0] += grid[i][0];
            for (int j = 1; j < N; j++)
                dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
        }
        return dp[N-1];
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        const int M = matrix.size(), N = matrix[0].size();
        vector<int> dp(N, 0);
        dp[0] = (matrix[0][0] == '1');
        int pre = 0, res = 0;
        for (int i = 0; i < M; i++)
        {
            pre = dp[0];
            dp[0] = (matrix[i][0] == '1');
            for (int j = 1; j < N; j++)
            {
                int tmp = dp[j];
                if (matrix[i][j] == '1')
                    dp[j] = min(dp[j-1], min(dp[j], pre)) + 1;
                else
                    dp[j] = 0;
                pre = tmp;
            }
            res = max(*max_element(dp.begin(), dp.end()), res);
        }
        return res*res;
    }
};

}

#endif