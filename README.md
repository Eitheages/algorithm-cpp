# 算法

## 查找算法

### 对分查找

#### 技巧：快速写出一个对分查找

以升序数组为例。
首先，大多数语言具有内置的函数以定位数组中大于/小于目标值的第一个/最后一个一个数，他们就是用二分查找实现的。C++中为`<algorithm>`库中的`std::lower_bound`,`std::upper_bound`它们的用法如下：

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
{
    vector<int> nums(5);
    for (int i = 0; i < 5; ++i)
        nums[i] = i * i;
    // nums = {0, 1, 4, 9, 16}
    auto it = lower_bound(nums.begin(), nums.end(), 3);
    cout << "The index of the biggest number smaller than 3 is "
            << it - nums.begin() << endl;
    return 0;
}
```

注：如果数组中不存在满足条件的数，返回值总是`nums.end()`。
Python中为内置库`bisect`中的`bisect_left`和`bisect_right`函数。摘录`help(bisect.bisect_left)`如下：

> bisect_left(a, x[, lo[, hi]]) -> index
>    Return the index where to insert item x in list a, assuming a is sorted.
>    
> The return value i is such that all e in a[:i] have e < x, and all e in a[i:] have e >= x.  So if x already appears in the list, i points just before the leftmost x already there.

即找到第一个**大于等于**（C++的两个函数不取等）目标值的数的下标。`bisect_right`函数找到的是第一个大于目标值的数的下标。如果不存在，它们都会返回`len(nums)`。
很多时候，这个算法需要手动实现。快速地写出这一对分查找算法十分重要，今把我的个人经验记录如下。

1. 首先确定题目需求：找到递增数组中大于（等于）/小于（等于）`targer`的第一个数/最后一个数的下标。考虑数组中不存在满足条件的数，我们需要返回一个值来标记这一事实，个人建议是返回`-1`或`nums.length`（视情况而定）；

2. 以==找到小于等于`target`的最后一个数的下标==这一问题为例，在极端情况，我们需要返回的应该是`-1`（表示数组中的所有数都严格大于`target`）。那么，查找的左边界就应该被设置为`-1`，因为如果设置成`0`，那么`-1`根本不可能作为查找结果；相应的，右边界应该被设置为`nums.length-1`（具体解释见后面）。同理，如果是大于（等于）类的问题，左边界应当设置为`0`而右边界设置为`nums.length`。于是我们定义：

   ```cpp
   int l = -1, r = nums.size() - 1;
   ```

3. 现在考虑对分查找的主体。我们规定`while`循环的条件判断句为`l < r`以避免出现死循环。通过简单的推理能发现，不论我们采用的是**向下取整**还是**向上取整**，循环结束的充要条件是`l == r`。也就是说，我们的返回值是`l`和`r`中的任意一个。

4. 对于循环中的条件分支，我们要注意一套固定的搭配格式：

   ```cpp
   l = m + 1;
   r = m;
   ```

   或者

   ```cpp
   l = m;
   r = m - 1;
   ```

   这两套搭配的合理性，请读者自行验证。我们考虑选取哪一套搭配时，需要回溯题目要求：能否取等。例如，我已经写下了这样的循环主体：

   ```cpp
   while (l < r)
   {
       int m = (l + r) >> 1; //暂时先用向下取整
       if (nums[m] <= target)
           l = ?
       else
           r = ?
   }
   ```

   思路很简单：例如，当前题目要求**小于等于**`target`，那么小于等于`target`的数应当被**保留**在查找区间中，因此，当`nums[m] <= target`时，应执行`r = m`。相应的，`else`下应当执行`l = m + 1`。

5. 我们已经有了以下算法：

   ```cpp
   int l = -1, r = nums.size() - 1;
   while (l < r)
   {
       int m = (l + r) >> 1;
       if (nums[m] <= target)
           l = m;
       else
           r = m - 1;
   }
   ```

   如今我们要做最关键的一步：**检验**。注意，这套技巧中，检验是必不可少的，而且我们检验的情况也是很简单的：我们只须考虑`l + 1 == m`的情况，这是跳出循环前的最后一步（必然的）。我们只须检验是否会出现**死循环**。

   > 我们不妨假设`[3, 4]`是最后的查找区间，且`target == 3`。容易发现，当计算机只差一步就可以返回正确答案时，它陷入了死循环。而算法中的其他部分都是确定的，唯一能改变的就只是`int m = (l + r) >> 1`这一步：我们采用了向下取整，而它造成了死循环。为了解决这一问题，我们将其改为向上取整。

   解释：采用向上/向下取整对其余的查找过程是没有实质影响的，但它决定了最后一步是否能正确地跳出循环。
   现在我们思考：为什么当初把查找的右边界设置为`nums.length-1`。如若不然，我们设置为`nums.length`，那么可能出现这样的情况：查找右边界没有改变，查找左边界一直在向右靠，直到等于`nums.length-1`，此时对两个边界求和并向上取整的结果是`nums.length`，那么立刻出现`IndexError`错误。
   (其实一般来说，小于（等于）用向上取整，反之用向下取整)

6. 最后总结一下，完整的函数（作为对照，用Python书写）：

   ```python
   from typing import List
   
   def lower_bound(nums: List[int], target: ...) -> int:
       l, r = -1, len(nums) - 1
       while l < r:
           m = (l + r + 1) >> 1
           if nums[m] <= target:
               l = m
           else:
               r = m - 1
       return l
   ```

   