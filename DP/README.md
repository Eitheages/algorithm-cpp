# 动态规划(Dynamic Programming)

classic.h文件记录了一个经典的问题：最长上升字串。  
算法的实训位置如下：  

## 单串(Single String)

+ ==801.使序列递增的最小交换次数== minSwap

  > 我们有两个长度相等且不为空的整型数组 A 和 B 。  
  > 我们可以交换 A[i] 和 B[i] 的元素。注意这两个元素在各自的序列中应该处于相同的位置。  
  > 在交换过一些元素之后，数组 A 和 B 都应该是严格递增的（数组严格递增的条件仅为A[0] < A[1] < A[2] < ... < A[A.length - 1]）。  
  > 给定数组 A 和 B ，请返回使得两个数组均保持严格递增状态的最小交换次数。假设给定的输入总是有效的。  
  >
  > > 示例：  
  > > 输入：A = [1,3,5,4], B = [1,2,3,7]  
  > > 输出：1  
  > > 解释：  
  > > 交换 A[3] 和 B[3] 后，两个数组如下：  
  > > A = [1, 3, 5, 7] ， B = [1, 2, 3, 4]  
  > > 两个数组均为严格递增的。  

  **写一下思路**：  
  首先理解什么叫“给定的输入总是有效的”。我们考虑**相邻的下标**，记
  $$
  m_1=\min\{A[i-1],B[i-1]\},m_2=\min\{A[i],B[i]\}\\
  M_1=\max\{A[i-1],B[i-1]\},M_2=\max\{A[i],B[i]\}
  $$
  我们断言：
  $$
  \text{“输入有效”}\Leftrightarrow m_1<m_2,M_1<M_2 \tag{1}
  $$
  证明：

  必要性。考虑反证法，如若不然，或者$m_1\geqslant m_2$​​​​，或者$M_1\geqslant M_2$​​​​。  
  先看前者，则易见$M_1\geqslant m_1\geqslant m_2$​​​​，从而$A[i-1],B[i-1]$​​​​均大于等于$m_2$​​​​，则输入不是“有效的”。  
  亦然可知后者也是不可能的情况。  
  充分性是显然的，只需调整位置使得$m_1,m_2$​​​​在同一数组即可。$\square$​​​​    
  我们不妨只调换$A[i],b[i]$​​​​，很显然，或者调换，或者不调换，**至少有一种方式**能使得数组满足目标。  
  颇须留意的是，满足$(1)$​​​​条件并不总能确定唯一的调换情况，**有可能调换和不调换均是满足题意的**（须在$(1)$​的基础上增添条件：$M_1<m_2$​）。  
  我们维护两个数组$a[i],b[i]$​​​​​​，定义：  

  > 在前$(i-1)$项已经严格递增的前提下：  
  > $a[i]$表示$A[i],B[i]$被调换的情况下，使得前$i$项严格递增的最少调换次数；  
  > $b[i]$表示$A[i],B[i]$未被调换的情况下，使得前$i$项严格递增的最少调换次数；  

  先考虑比较简单的$b[i]$，即假设第$i$项不被调换，此时也有两种情况：  

  > 1. $(i-1)$项可以不调换；
  > 2. $(i-1)$项可以调换。

  注意这里的用词。根据之前的推导，这两种情况并非互斥的，**==至少有一个成立，并且有可能同时成立==**。因此，在写代码的时候一定不要用else连接判断条件，而是用两个并列的if语句。  
  $a[i]$​的情况是类似的，只不过记得要加1。  
  为了更加清晰，我们用0表示不调换，1表示调换，列出表格（状态转移方程）：

  | 下方：i；右方：i-1 |        0        |        1        |
  | :----------------: | :-------------: | :-------------: |
  |         0          |  $b[i]=b[i-1]$  |  $b[i]=a[i-1]$  |
  |         1          | $a[i]=b[i-1]+1$ | $a[i]=a[i-1]+1$ |

  可以看到，按理来说我们要写四个判断语句。但是事实上，同时调换和同时不调换的情况是一致的，只有一个调换的情况也是一致的，所以我们只需要两个判断语句。 
  于是我们便可以作出解答。

+ ==790.多米诺和托米诺平铺== numTilings

  > 有两种形状的瓷砖：一种是 2x1 的多米诺形，另一种是形如 "L" 的托米诺形。两种形状都可以旋转。  
  >
  > > XX  <- 多米诺  
  > > XX  <- "L" 托米诺  
  > > X
  >
  > 给定 $N$($1\leqslant N\leqslant 1000$​) 的值，有多少种方法可以平铺 2 x N 的面板？返回值 mod 10^9 + 7。  
  > （平铺指的是每个正方形都必须有瓷砖覆盖。两个平铺不同，当且仅当面板上有四个方向上的相邻单元中的两个，使得恰好有一个平铺有一个瓷砖占据两个正方形。）
  >
  > > 示例:
  > > 输入: 3
  > > 输出: 5
  > > 解释: 
  > > 下面列出了五种不同的方法，不同字母代表不同瓷砖：
  > > XYZ XXZ XYY XXY XYY
  > > XYZ YYZ XZZ XYY XXY

  规划思路：$dp[i]$​的含义是：**当前列被铺满的条件下**，额外使得后一列中的某些行被铺满的方法数。
  例如：(记当前列为$k$​列)
  $dp[0b00]$​代表$k$​列被铺满的条件下，使得$k+1$​列每一行都没有被铺到的方法数；
  $dp[0b11]$​代表$k$​列被铺满的条件下，使得$k+1$​​​列也被铺满的方法数。
  因而给出状态转移方程：
  ![如图](https://pic.leetcode-cn.com/Figures/790/possible.png)

+ ==300.Longest Increasing Subsequence== lengthOfLIS

  > Given an integer array nums, return the length of the longest strictly increasing subsequence.
  >
  > A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
  >
  > **Constraints:**
  >
  > + $1 <= nums.length <= 2500$
  > + $-10^4 <= nums[i] <= 10^4$​

+ ==376.Wiggle Subsequence== wiggleMaxLength **attention!!**

  > A **wiggle sequence** is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.
  >
  > + For example, `[1, 7, 4, 9, 2, 5]` is a **wiggle sequence** because the differences `(6, -3, 5, -7, 3)` alternate between positive and negative.
  > + In contrast, `[1, 4, 7, 2, 5]` and `[1, 7, 4, 5, 5]` are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.
  >
  > A **subsequence** is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.
  >
  > Given an integer array `nums`, return *the length of the longest **wiggle subsequence** of* `nums`.

  Note: Define $up[i]$​​ as the length of the longest wiggle subsequence of `nums[0: i]`, plus which, the end two number most be increasing; $down[i]$​​, on the contrary, is restricted to end with two decreasing number. An important point is that the subsequence don't have to end up with `nums[i-1]`.

+ ==673.最长递增子序列的个数== findNumberOfLIS

  > 给定一个未排序的整数数组，找到最长**严格**递增子序列的个数。
  
+ ==354.俄罗斯套娃信封问题== maxEnvelopes

  > 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
  >
  > 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
  >
  > 请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
  >
  > 注意：不允许旋转信封。
  >
  > 示例1：
  >
  > 输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
  > 输出：3
  > 解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
  >
  > 示例2：
  >
  > 输入：envelopes = [[1,1],[1,1],[1,1]]
  > 输出：1
  
  思路简述：按宽度升序排列，按长度降序排序，即可忽略宽度维度，只考虑长度维度。
  
+ ==918.环形子数组的最大和== maxSubarraySumCircular

  > 给定一个由整数数组 A 表示的环形数组 C，求 C 的非空子数组的最大可能和。
  >
  > 在此处，环形数组意味着数组的末端将会与开头相连呈环状。（形式上，当0 <= i < A.length 时 C[i] = A[i]，且当 i >= 0 时 C[i+A.length] = C[i]）
  >
  > 此外，子数组最多只能包含固定缓冲区 A 中的每个元素一次。（形式上，对于子数组 C[i], C[i+1], ..., C[j]，不存在 i <= k1, k2 <= j 其中 k1 % A.length = k2 % A.length）

  思路：只看图，来自美国站大佬 [Solution](https://assets.leetcode.com/users/motorix/image_1538888300.png)
  极端情况：对于和最大的子数组（非环形），它非正当且仅当数组中没有正数，并且此时，和最大的子数组等于最大的那一个数，和最小的子数组等于整个数组。于是可知：当`max_num`非正时，应该无条件取`max_num`，因为和最小的子数组包含了所有的数。


+ ==363.矩形区域不超过 K 的最大数值和== maxSumSubmatrix

  > Given an `m x n` matrix `matrix` and an integer `k`, return *the max sum of a rectangle in the matrix such that its sum is no larger than* `k`.
  >
  > It is **guaranteed** that there will be a rectangle with a sum no larger than `k`.

  老实说，感觉这道题跟DP没啥关系...

+ ==198.打家劫舍== rob

  > You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.
  >
  > Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight **without alerting the police***.
  >
  > 中文释义：不能同时偷相邻的房间

+ ==213.打家劫舍 II==

  > All houses at this place are **arranged in a circle.**

  其实只需要对[1: n]，[0: n-1]分别做打家劫舍I的动态规划即可

+ ==740.删除并获得点数== deleteAndEarn

  > You are given an integer array `nums`. You want to maximize the number of points you get by performing the following operation any number of times:
  >
  > + Pick any `nums[i]` and delete it to earn `nums[i]` points. Afterwards, you must delete **every** element equal to `nums[i] - 1` and **every** element equal to `nums[i] + 1`.
  >
  > Return *the **maximum number of points** you can earn by applying the above operation some number of times*.
  >
  > **Constraints:**
  >
  > + $1 <= nums.length <= 2 * 10^4$
  > + $1 <= nums[i] <= 10^4$​

  个人思路：桶排序。耗时还意外地短，就是耗空间。

+ ==55.Jump Game==  canJump

  > You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in the array represents your maximum jump length at that position.
  >
  > Return `true` *if you can reach the last index, or* `false` *otherwise*.
  >
  > **Constraints:**
  >
  > + $1 <= nums.length <= 10^4$
  > + $0 <= nums[i] <= 10^5$
  >
  > 释义：`nums[i]`记录的是最大能跳的格数

  个人思路：从后往前遍历，迭代器`p`依次指向跳跃到末尾的路线，遍历结束时，`p`指向路线的开端，而若开端不是`nums.begin()`，说明从第一个数无法跳到末尾。与贪心算法不同的是，这里`p`遍历的格子是采取最劣情况下的跳跃路线。核心依据：如果能跳到第`i`个数，一定能跳到第`i`个数之前的每一个数。
  LeetCode上一个比较好（生动）的思路：能量理论，走一格消耗一个能量，如果走到的格子上的数比自己身上携带的能量数更多，则将能量替换为格子上的数。本质上是一个贪心算法。
  比较正统的贪心算法：

  ```cpp
  bool canJump(vector<int>& nums) {
      int k = 0; //标记最远能到达的位置
      for (int i = 0; i < nums.size(); i++) {
          if (i > k) return false; //快就快在这里return了
          k = max(k, i + nums[i]);
      }
      return true;
  }
  ```

+ ==45.Jump Game II== 

  > Your goal is to reach the last index in the minimum number of jumps.
  >
  > You can assume that you can always reach the last index.

+ ==1388.3n 块披萨==

+ ==1567.Maximum Length of Subarray With Positive Product==  getMaxLen  **attention!!**

  > Given an array of integers `nums`, find the maximum length of a subarray where the product of all its elements is positive.
  >
  > A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
  >
  > Return *the maximum length of a subarray with positive product*.
  >
  > **Constraints:**
  >
  > + $1 <= nums.length <= 10^5$
  > + $-10^9 <= nums[i] <= 10^9$
  
  我写了一个分治的算法，但是出现Runtime Error（本地编译器正确），标程的做法有空再做一次。

+ ==1014.Best Sightseeing Pair==  maxScoreSightseeingPair

  > You are given an integer array `values` where values[i] represents the value of the `ith` sightseeing spot. Two sightseeing spots `i` and `j` have a **distance** `j - i` between them.
  >
  > The score of a pair (`i < j`) of sightseeing spots is `values[i] + values[j] + i - j`: the sum of the values of the sightseeing spots, minus the distance between them.
  >
  > Return *the maximum score of a pair of sightseeing spots*.
  >
  > **Constraints:**d
  >
  > + $2 <= values.length <= 5 * 10^4$
  > + $1 <= values[i] <= 1000$​
  
+ ==122.Best Time to Buy and Sell Stock II== maxProfit2

  > You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `ith` day.
  >
  > On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any time. However, you can buy it then immediately sell it on the **same day**.
  >
  > Find and return *the **maximum** profit you can achieve*.
  >
  > **Constraints:**
  >
  > + $1 <= prices.length <= 3 * 10^4$
  > + $0 <= prices[i] <= 10^4$​

  个人思路：非常简单。因为严格递增序列中，取第一个数和最后一个数，其差值最大。也就是说，如果数组递增，就不要卖股票；一旦数组没有严格递增，也就是后一天的股价小于等于前一天的，立刻在前一天抛出股票。设计算法时，我们可以假设股票可以当日卖出：当天买当天卖，和完全不购买空过一天是完全等价的。

  > 因为交易次数不受限，如果可以把所有的上坡全部收集到，一定是利益最大化的。

+ ==309.Best Time to Buy and Sell Stock with Cooldown== maxProfit3

  > After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
  > **Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
  
  这个系列的题目，有空认真想一想。
  
+ ==413.Arithmetic Slices== numberOfArithmeticSlices

  > An integer array is called arithmetic if it consists of **at least three elements** and if the difference between any two consecutive elements is the same.
  >
  > + For example, `[1,3,5,7,9]`, `[7,7,7,7]`, and `[3,-1,-5,-9]` are arithmetic sequences.
  >
  > Given an integer array `nums`, return *the number of arithmetic **subarrays** of* `nums`.
  >
  > A **subarray** is a contiguous subsequence of the array.

  I only tried once to receive an AC. It's too easy.

+ ==91.Decode Ways==

  > A message containing letters from `A-Z` can be **encoded** into numbers using the following mapping:
  >
  > ```
  > 'A' -> "1"
  > 'B' -> "2"
  > ...
  > 'Z' -> "26"
  > ```
  >
  > To **decode** an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, `"11106"` can be mapped into:
  >
  > + `"AAJF"` with the grouping `(1 1 10 6)`
  > + `"KJF"` with the grouping `(11 10 6)`
  >
  > Note that the grouping `(1 11 06)` is invalid because `"06"` cannot be mapped into `'F'` since `"6"` is different from `"06"`.
  >
  > Given a string `s` containing only digits, return *the **number** of ways to **decode** it*.
  >
  > The test cases are generated so that the answer fits in a **32-bit** integer.
  >
  > **Constraints:**
  >
  > + 1 <= s.length <= 100
  > + `s` contains only digits and may contain leading zero(s).
  
+ ==264.Ugly Number II== nthUglyNumber

  > An **ugly number** is a positive integer whose prime factors are limited to `2`, `3`, and `5`.
  >
  > Given an integer `n`, return *the* `nth` ***ugly number***.

  解法：合并三个严格递增数组：被2整除，被3整除，被5整除；运用三指针。

+ ==96.Unique Binary Search Trees== numTrees

  > Given an integer `n`, return *the number of structurally unique **BST'**s (binary search trees) which has exactly* `n` *nodes of unique values from* `1` *to* `n`.
  

## 矩阵类(Matrix)

+ ==931.Minimum Falling Path Sum== minFallingPathSum

  > Given an `n x n` array of integers `matrix`, return *the **minimum sum** of any **falling path** through* `matrix`.
  >
  > A **falling path** starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position `(row, col)` will be `(row + 1, col - 1)`, `(row + 1, col)`, or `(row + 1, col + 1)`.
  >
  > **Constraints:**
  >
  > + `n == matrix.length == matrix[i].length`
  > + `1 <= n <= 100`
  > + `-100 <= matrix[i][j] <= 100`

+ ==120.Triangle== minimumTotal

  > Given a `triangle` array, return *the minimum path sum from top to bottom*.
  >
  > For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row
  
+ ==1314.Matrix Block Sum== matrixBlockSum

  > Given a `m x n` matrix `mat` and an integer `k`, return *a matrix* `answer` *where each* `answer[i][j]` *is the sum of all elements* `mat[r][c]` *for*:
  >
  > + `i - k <= r <= i + k,`
  > + `j - k <= c <= j + k`, and
  > + `(r, c)` is a valid position in the matrix.

+ ==304.Range Sum Query 2D - Immutable== NumMatrix sumRegion

  > Given a 2D matrix `matrix`, handle multiple queries of the following type:
  >
  > + Calculate the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
  >
  > Implement the NumMatrix class:
  >
  > + `NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.
  > + `int sumRegion(int row1, int col1, int row2, int col2)` Returns the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.
  
+ ==62.Unique Paths== uniquePaths

  > There is a robot on an `m x n` grid. The robot is initially located at the **top-left corner** (i.e., `grid[0][0]`). The robot tries to move to the **bottom-right corner** (i.e., `grid[m - 1][n - 1]`). The robot can only move either down or right at any point in time.
  >
  > Given the two integers `m` and `n`, return *the number of possible unique paths that the robot can take to reach the bottom-right corner*.
  >
  > The test cases are generated so that the answer will be less than or equal to $2 * 10^9$​.
  >
  > **Constraints:**
  >
  > + `1 <= m, n <= 100`
  
+ ==63.Unique Paths II== uniquePathsWithObstacles

  > A robot is located at the top-left corner of a `m x n` grid (marked 'Start' in the diagram below).
  >
  > The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
  >
  > Now consider if some obstacles are added to the grids. How many unique paths would there be?
  >
  > An obstacle and space is marked as `1` and `0` respectively in the grid.

  ```cpp
  class Solution {
  public:
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
  };
  ```

+ ==面试题 17.24. 最大子矩阵== getMaxMatrix

+ ==64.Minimum Path Sum== minPathSum

  > Given a `m x n` `grid` filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
  >
  > **Note:** You can only move either down or right at any point in time.

+ ==221.Maximal Square== maximalSquare   **attention!!**

  > Given an `m x n` binary `matrix` filled with `0`'s and `1`'s, *find the largest square containing only* `1`'s *and return its area*.

  `dp[i][j]` is defined to be the max size of the square that contains `matrix[i][j]`. Thus we have:
  $$
  dp\left[ i \right] \left[ j \right] =\begin{cases}
  	0&		matrix\left[ i \right] \left[ j \right] =0\\
  	\min \left(dp\left[ i-1 \right] \left[ j-1 \right] , dp\left[ i-1 \right] \left[ j \right] ,dp\left[ i \right] \left[ j-1 \right] \right) +1&		matrix\left[ i \right] \left[ j \right] =1\\
  \end{cases}
  $$



## 双串(Double String)

Most of the time, $\mathrm{dp}[i][j]$ is determined by $dp[i+1][j]$, $dp[i][j-1]$ and $dp[i+1][j-1]$.
As the picture shows:
![picture alt](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/06/2-2-2.png)



+ ==5.Longest Palindromic Substring== longestPalindrome  **attention!!**

  > Given a string `s`, return *the longest palindromic substring* in `s`.
  >
  > **Constraints:**
  >
  > + `1 <= s.length <= 1000`
  > + `s` consist of only digits and English letters.

+ ==516.Longest Palindromic Subsequence== longestPalindromeSubseq **attention!!**

  > Given a string `s`, find *the longest palindromic **subsequence**'s length in* `s`.
  >
  > A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
  >
  > **Constraints:**
  >
  > + `1 <= s.length <= 1000`
  > + `s` consists only of lowercase English letters.
  
  In a common solution, $dp[i][j]$​​​​​ is defined as the length of the longest palindromic subsequence of `s[i: j+1]`
  In a special solution, the original string `s` is reversed to be `ss`, and the next step is to find the length of the longest common subsequence of `s` and `ss`. It turns out to be Problem 1143.
  
+ ==1143.Longest Common Subsequence== longestCommonSubsequence  **attention!!**

  > Given two strings `text1` and `text2`, return *the length of their longest **common subsequence**.* If there is no **common subsequence**, return `0`.
  >
  > A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
  >
  > + For example, `"ace"` is a subsequence of `"abcde"`.
  >
  > A **common subsequence** of two strings is a subsequence that is common to both strings.
  >
  > **Constraints:**
  >
  > + `1 <= text1.length, text2.length <= 1000`
  > + `text1` and `text2` consist of only lowercase English characters.

  Define $dp[i][j]$​​​ as the length of the longest common subsequence of `s1[0: i]` and `s2[0: j]` (the uses of [i: j] is borrowed from Python). We have State Transition Equation:
  $$
  dp[i][j]=
  \begin{cases}
      dp[i-1][j-1]+1 & s1[i-1]=s2[j-1]\\
      \max\{dp[i-1][j], dp[i][j-1]\} & s1[i-1]\not= s2[j-1]
  \end{cases}
  $$
  
+ ==392.Is Subsequence== isSubsequence

  > Given two strings `s` and `t`, return `true` *if* `s` *is a **subsequence** of* `t`*, or* `false` *otherwise*.

  Two important solutions:

  1. Two Pointers. It's easy to understand.

     ```cpp
     bool isSubsequence(string s, string t) {
         int i = 0, j = 0;
         while (i < s.length())
         {
             char tmp = s[i];
             while (j < t.length() && t[j] != tmp)
                 j++;
             if (j == t.length())
                 return 0;
             else
                 j++;
             i++;
         }
         return 1;
     }
     ```

  2. Dynamic Programming. Though "two-pointers" is easy to understand, when dealing with an array of `s`, the time may be wasting. Therefore, preprocessing string `t` is a good idea.
     We define $dp[i][j]$​​ as the first place that character $j$​​ shows up after `t[i]`. To initalize, obviously, $dp[i][t[i]]$​​ equals `i`. We have:
     $$
     dp[i][j]=
     \begin{cases}
     i & t[i]=j\\
     dp[i+1][j] & t[i] \not= j
     \end{cases}
     $$
  
+ ==72.Edit Distance== minDistance  **attention!!**

  > Given two strings `word1` and `word2`, return *the minimum number of operations required to convert `word1` to `word2`*.
  >
  > You have the following three operations permitted on a word:
  >
  > + Insert a character
  > + Delete a character
  > + Replace a character
  >
  > **Constraints:**
  >
  > + `0 <= word1.length, word2.length <= 500`
  > + `word1` and `word2` consist of lowercase English letters.

