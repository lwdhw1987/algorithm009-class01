# 寻找半有序数组中间无序的地方

## 题意理解
给定半有序数据，中间无序的地方是指某个索引对应的值大于后一个值。即`nums[i] > nums[i+1]`。

* [3, 4, 5, 6, 7, 0, 1, 2], 7大于后面的0，7对应的索引为4，所以中间无序的地方索引为4
* [6, 7, 0, 1, 2, 4, 5], 中间无序的地方索引为1
* [7, 0, 1, 2, 4, 5, 6], 中间无序的地方索引为0
* [0, 1, 2, 4, 5, 6], 都是有序的，所以返回-1

## 思路
1.使用二分法遍历数据，并设置循环条件为`left < right`, 循环结束时，数组中仍有一个边界没有处理，其形式为[left, left]或者[right, right],
  如果left或者right小于nums.size() - 1，还需要判断nums[left] > nums[left + 1]或nums[right] > nums[right + 1]的情况。

2.计算`mid = left + (right - left)/2`，因为循环体中`left < right`，所以`mid + 1`不会越界，如果有`nums[mid] > nums[mid + 1]`，说明找到了无序地方对应的索引。返回`mid`。

3.如果没有找到，通过`nums[mid]`和`nums[left]`关系判断，数组的哪一段是有序的，无序的一段有两种情况`[left, mid - 1]`或者`[mid + 1, right]`。

4.进一步在无序分段`[left, mid - 1]`或`[mid + 1, right]`中寻找无序点，会有三种情况，无序点刚好在无序分段的mid索引，此时可以直接返回。另外两种情况就是左右边界`[left, left]`或`[right, right]`。这两种情况需要在循环体外求解。如果仍未找到无序点，说明整个数组都是有序的，应该返回-1。

## 代码
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[mid + 1]) {
                return mid;
            }
            
            if (nums[mid] >= nums[left]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        
        if (left != nums.size() - 1 && nums[left] > nums[left+1]) {
            // cout << nums[left] << ',' << nums[left+1] << endl;
            return left;
        } 

        return -1;
    }
};
```
