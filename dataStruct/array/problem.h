#ifndef Pro_h
#define Pro_h

#include "basic.h"
using namespace std;

namespace A{
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int n = mat[0].size()-1;
        int m = mat.size()-1;
        int j,k,i;
        vector<int> res;
        for (k=0;k<=m+n;++k){
            if (k%2==1){
                j = k<n?k:n;
                for (i=k-j;i<=m&&j>=0;++i,--j) {
                    res.emplace_back(mat[i][j]);
                }
            }else{
                i = k<m?k:m;
                for (j=k-i;i>=0&&j<=n;++j,--i) {
                    res.emplace_back(mat[i][j]);
                }
            }

        }
        return res;
    }

    string longestCommonPrefix(vector<string>& strs) {
        string res = strs[0];
        int j;
        for (int i=1;i<strs.size();i++){
            if (strs[i]=="") {
                res = "";
                break;
            }
            string &temp = strs[i];
            for (j=0;j<temp.length()&&j<res.length();++j) {
                if (temp[j]!=res[j]) break;
            }
            if (j<res.length()) res.erase(j);
        }
        return res;
    }

    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i=0;i<nums.size();i+=2){res+=nums[i];}
        return res;
    }

    vector<int> twoSum(vector<int>& numbers, int target) {
        // 遍历
        // for (int i=0;i<numbers.size();i++){
        //     int low = i+1, high = numbers.size()-1, key = target - numbers[i], m;
        //     while (low<=high) {
        //         m = (low+high)/2;
        //         if (numbers[m]==key) break;
        //         if (numbers[m]>key) high = m-1;
        //         else low = m+1;
        //     }
        //     if (numbers[m]==key) return {i+1, m+1};
        // }
        // return {-1, -1};

        // 双指针
        int low = 0, high = numbers.size()-1;
        while (low!=high) {
            int key = numbers[low]+numbers[high];
            if (key>target) high--;
            else if (key<target) low++;
            else break;
        }
        if (low == high) return {-1, -1};
        return {low+1, high+1};
    }

    int removeElement(vector<int>& nums, int val) {
        int f = 0, s = 0;
        while (f<nums.size()) {
            if (nums[f]!=val) {
                nums[s++] = nums[f];
            }
            f++;
        }
        return s;

        // 利用题目特性：可以改变元素顺序
        // int i = 0, j = nums.size()-1;
        // while (i!=j) {
        //     if (nums[i]==val) nums[i] = nums[(j--)-1];
        //     else i++;
        // }
        // return i;
    }

    int findMaxConsecutiveOnes(vector<int>& nums) {
        int i, j, res=0;
        for (i=0;i<nums.size();++i) {
            if (nums[i]==1) {
                j = i+1;
                while (j<nums.size()&&nums[j]==1) j++;
                if (j-i>res) res = j-i;
                i = j-1;
            }
        }
        return res;
    }

    int minSubArrayLen(int target, vector<int>& nums) {
        int i(0), j(0), res(INT_MAX), temp(0);
        while (j<nums.size()) {
            temp += nums[j++];
            while (temp>=target) {
                temp-=nums[i];
                if (temp<target) {
                    int length = j-i;
                    if (length<res) res = length;
                }
                i++;
            }
        }
        return res==INT_MAX?0:res;
    }

    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; ++i) {
            for (int j = i; j > 0; --j) {
                row[j] += row[j - 1];
            }
        }
        return row;
        // 根据递推公式，也可以这么写
        // vector<int> row(rowIndex + 1);
        // row[0] = 1;
        // for (int i=1;i<=rowIndex;++i) {
        //     row[i] = 1LL*row[i-1]*(rowIndex+1-i)/i;
        // }
        // return row;
    }

    string reverseWords(string s) {
        int i(0), j(0);
        while (i<s.length()) {
            while (j<s.length()&&s[j]!=' ') j++;
            int t = j+1;
            for (j--;(j-i)>0;i++,j--) {
                swap(s[i], s[j]);
            }
            i = t;
            j = t;
        }
        return s;
    }

    int findMin(vector<int>& nums) {
        int i=0, j=nums.size()-1;
        while (i+1<j) {
            int m = (i+j)/2;
            if (nums[m]>=nums[i]&&nums[i]>nums[j]) i=m;
            else j=m;
        }
        return nums[i]>nums[j]?nums[j]:nums[i];
    }

    int removeDuplicates(vector<int>& nums) {
        int i=0,j=0;
        while (j<nums.size()) {
            if (nums[i]!=nums[j]) nums[++i] = nums[j];
            j++;
        }
        // while (deletnum--) nums.pop_back();
        nums.erase(nums.begin()+i+1,nums.end());
        return i+1;
    }

    void moveZeroes(vector<int>& nums) {
        if (nums.size()==0) return;
        int i=0,j=0;
        while (j<nums.size()) {
            if (nums[j]!=0) swap(nums[i++], nums[j]);
            j++;
        }
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = -1, j = matrix.size()-1, m;
        while (i < j)
        {
            m = (i+j+1) >> 1;
            if (matrix[m][0] <= target)
                i = m;
            else
                j = m-1;
        }
        if (i == -1)
            return false;
        int k = i;
        i = 0, j = matrix[k].size()-1;
        while (i <= j)
        {
            m = (i+j) >> 1;
            if (matrix[k][m] == target)
                return true;
            else if (matrix[k][m] < target)
                i = m+1;
            else
                j = m-1;
        }
        return false;
    }
};
}
#endif