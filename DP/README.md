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

+ 790.多米诺和托米诺平铺

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
  
  思路：只看图，来自美国站大佬[Solution](https://assets.leetcode.com/users/motorix/image_1538888300.png)
  
+ 面试题 17.24. 最大子矩阵 getMaxMatrix

+ 363.矩形区域不超过 K 的最大数值和 maxSumSubmatrix

  > Given an `m x n` matrix `matrix` and an integer `k`, return *the max sum of a rectangle in the matrix such that its sum is no larger than* `k`.
  >
  > It is **guaranteed** that there will be a rectangle with a sum no larger than `k`.

  老实说，感觉这道题跟DP没啥关系...

+ 198.打家劫舍 rob

  > You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.
  >
  > Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight **without alerting the police***.
  >
  > 中文释义：不能同时偷相邻的房间

+ 213.打家劫舍 II

  > All houses at this place are **arranged in a circle.**

  其实只需要对[1: n]，[0: n-1]分别做上述动态规划即可

+ 740.删除并获得点数

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

  个人思路：桶排序。耗时还以外的短，就是耗空间。

+ 1388.3n 块披萨

