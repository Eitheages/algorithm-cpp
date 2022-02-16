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

### 238. Product of Array Except Self

#### Problem

Given an integer array `nums`, return *an array* `answer` *such that* `answer[i]` *is equal to the product of all the elements of* `nums` *except* `nums[i]`.

The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

You must write an algorithm that runs in `O(n)` time and without using the division operation.

**Constraints:**

+ `2 <= nums.length <= 105`
+ `-30 <= nums[i] <= 30`
+ The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

**Follow up:** Can you solve the problem in `O(1) `extra space complexity? (The output array **does not** count as extra space for space complexity analysis.)

### 435. Non-overlapping Intervals

#### Problem

Given an array of intervals `intervals` where `intervals[i] = [starti, endi]`, return *the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping*.

**Constraints:**

+ `1 <= intervals.length <= 105`
+ `intervals[i].length == 2`
+ `-5 * 104 <= starti < endi <= 5 * 104`

### 560. Subarray Sum Equals K

#### Problem

Given an array of integers `nums` and an integer `k`, return *the total number of continuous subarrays whose sum equals to `k`*.

**Constraints:**

+ `1 <= nums.length <= 2 * 104`
+ `-1000 <= nums[i] <= 1000`
+ `-107 <= k <= 107`

### 350. Intersection of Two Arrays II

#### Problem

Given two integer arrays `nums1` and `nums2`, return *an array of their intersection*. Each element in the result must appear as many times as it shows in both arrays and you may return the result in **any order**.

**Constraints:**

+ `1 <= nums1.length, nums2.length <= 1000`
+ `0 <= nums1[i], nums2[i] <= 1000`

**Follow up:**

+ What if the given array is already sorted? How would you optimize your algorithm?
+ What if `nums1`'s size is small compared to `nums2`'s size? Which algorithm is better?
+ What if elements of `nums2` are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

#### Solution

The question itself is easy but the 3rd follow up question is worth-thinking.

+ If only `nums2` cannot fit in memory, put all elements of nums1 into a HashMap, read chunks of array that fit into the memory, and record the intersections.

+ If both `nums1` and `nums2` are so huge that neither fit into the memory, sort them individually (**external sort**), then read 2 elements from each array at a time in memory, record intersections.

Emphasis: **merge-sort** is naturally an external sort.
