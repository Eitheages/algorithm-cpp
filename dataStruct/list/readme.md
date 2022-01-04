# 程序位置简述

basic包含了矩阵类，以及几个成员函数。  
算法实训位置：

+ 二维数组(矩阵)

  + 对角线遍历矩阵。findDiagonalOrder

+ 字符串

  + 最长公共前缀。longestCommonPrefix
  + 最长回文子串(还不会写 学了动态规划来写)。longestPalindrome

+ 双指针技巧

  + 数组拆分 I  arrayPairSum
    >给定长度为 2n 的整数数组 nums ，你的任务是将这些数分成 n 对, 例如 (a1, b1), (a2, b2), ..., (an, bn) ，使得从 1 到 n 的 min(ai, bi) 总和最大。返回该 最大总和。

    顺带一提，用`python`只需要两句话：  

    ```python
    nums.sort()
    return sum(nums[::2])
    ```

  + 两数之和 II - 输入有序数组 twoSum  
    >给定一个已按照 非递减顺序排列  的整数数组 numbers ，请你从数组中找出两个数满足相加之和等于目标数 target 。假设仅存在一个有效答案，下标从1开始。
  + 移除元素 removeElement
    >给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。  
    >不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。  
    >元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

    `python`的写法如下：

    ```python
    f,s = 0,0
    while f < len(nums):
      if nums[f] != val:
        nums[s] = nums[f]
        s += 1
      f += 1
    return s
    ```
  
  + 最大连续1的个数 findMaxConsecutiveOnes
  + 长度最小的子数组
    >给定一个含有 n 个正整数的数组和一个正整数 target 。
    >找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
    >如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。

+ 综合练习
  + 杨辉三角 getRow
    >给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。
  + 反转字符串中的单词 reverseWords
    >给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

    你`python`一行就够了：

    ```python
    # 先拆分，再翻转，最后拼接
    return " ".join(word[::-1] for word in s.split(' '))
    # 先翻转，再拆分，又分别翻转，最后拼接
    return " ".join(s[::-1].split(' ')[::-1])
    ```

  + 寻找旋转排序数组中的最小值 findMin
    >看链接就知道题目了 **[图片](https://assets.leetcode-cn.com/solution-static/153/1.png)**
  + 删除排序数组中的重复项 removeDuplicates
    >给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
    >不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

    `python`的写法如下：（不难，但是写了就放上来了w）

    ```python
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0
        i,j=0,0
        while j<len(nums):
            if nums[i]!=nums[j]:
                i+=1
                nums[i] = nums[j]
            j+=1
        for k in range(i+1,len(nums)):
            nums.pop()
        return i+1
    ```

    顺带一提，这道题中，是否删除尾部元素似乎不关键。

  + 移动零 moveZeroes
    >给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
