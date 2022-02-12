### 1. Two Sum `twoSum`

#### Problem

Given an array of integers `nums` and an integer `target`, return *indices of the two numbers such that they add up to `target`*.

You may assume that each input would have ***exactly\* one solution**, and you may not use the *same* element twice.

You can return the answer in any order.

**Constraints:**

+ `2 <= nums.length <= 104`
+ `-109 <= nums[i] <= 109`
+ `-109 <= target <= 109`
+ **Only one valid answer exists.**

### 240. Search a 2D Matrix II

#### Problem

Write an efficient algorithm that searches for a value `target` in an `m x n` integer matrix `matrix`. This matrix has the following properties:

+ Integers in each row are sorted in ascending from left to right.
+ Integers in each column are sorted in ascending from top to bottom.

**Constraints:**

+ `m == matrix.length`
+ `n == matrix[i].length`
+ `1 <= n, m <= 300`
+ `-10^9 <= matrix[i][j] <= 10^9`
+ All the integers in each row are **sorted** in ascending order.
+ All the integers in each column are **sorted** in ascending order.
+ `-10^9 <= target <= 10^9`

#### Solution

1. Binary search.
   Each time exclude a half row/column of numbers.
2. Z-shape search.
   Beginning with the top right number. If the number is bigger than the target, move to the previous column. If the number is smaller, move to the next row.
   Explanation: the search interval is the current number to the bottom left number. Exclude a row or a column each time.

