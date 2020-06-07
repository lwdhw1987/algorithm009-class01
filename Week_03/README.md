# 分治与回溯学习总结
### 二分查找
二分查找是分治思想的一种具体体现，必须在一个有序序列中使用二分查找，每一次查找先锁定中间值，然后将查找问题划分成左右两部分查找的子问题。二分查找的难点在于拆分子问题时候的边界处理和返回值处理，从LeetCode上找到了[三个模版](https://leetcode-cn.com/explore/learn/card/binary-search/209/template-i/835/)，我试着从自己的角度去理解并记忆。
- 模版1:
```cpp
// 初始值left = 0, right = nums.size() - 1
int binarySearch(vector<int>& nums, int target, int left, int right){
  if (left > right) {
    return -1;
  }
  
  int mid = left + (right - left) / 2;
  if (nums[mid] == target) {
    return mid;
  }
  else if (nums[mid] < target) {
    // [mid + 1, right]
    return binarySearch(nums, target, mid + 1, right);
  }
  else {
    // [left, mid - 1]
    return binarySearch(nums, target, left, mid - 1);
  }
}
```
`int mid = left + (right - left) / 2`是防止(left + right)溢出，上述代码采用左右闭区间的表示方式，查找区间表示为[L, R], 划分子问题后，查找左右子区间分别为[L, mid - 1], [mid + 1, R]。**查找过程可以接触到左右边界值**，例如当区间长度为2时，且nums[mid] < target，查找子区间变为[R, R]，否则查找子区间变为[L, L]。如果能够找到，函数就会返回L或着R，否则再进一步，查找子区间变为[L, L - 1]或[R + 1, R]，此时满足递归结束条件返回-1。

- 模版2:
```cpp
// 初始值left = 0, right = nums.size()
int binarySearch(vector<int>& nums, int target, int left, int right){
  if (left == nums.size()) return -1;
  if (left == right && nums[left] == target) {
    return (nums[left] == target ? left : -1);
  }
  
  int mid = left + (right - left) / 2;
  if(nums[mid] == target){ return mid; }
  else if(nums[mid] < target) { 
    // [mid + 1, right)
    return binarySearch(nums, target, mid + 1, right);
  }
  else {
    // [left, mid)
    return binarySearch(nums, target, left, mid);
  }
}
```
模版2代码采用左闭右开的的表示方式，查找区间表示为[L, R)，划分子问题后，左右区间分别为[L, mid), [mid + 1, R)。**查找过程只能接触到左边界**, 当查找区间的长度为2，且nums[mid] < target，查找子区间变为[R, R)或者[L, L)，此时已经满足递归结束条件，但是仍要判断nums[R] == target或者nums[L] == target。

- 模版3
```cpp
// 初始值left = 0, right = nums.size() - 1
int binarySearch(vector<int>& nums, int target){
    if (left + 1 == right) {
      if (nums[left] == target) return left;
      else if (nums[right] == target) return right;
      else return -1;
    }
    
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) {
      return binarySearch(nums, taget, mid, right);
    }
    else {
      return binarySearch(nums, taget, left, mid);
    }
}
```
模版3代码采用左右闭区间的表示方式，查找区间表示为[L, R], 划分子问题后，左右区间分别为[L, mid], [mid, R]。**查找过程无法接触到左右边界**，当区间长度为2，此时已经满足递归结束条件，但是仍要判断nums[L] == target或者nums[R] == target。 

### 总结，从二分查找过程对左右边界的访问可以分成三种模版，对应不同的代码需求。对于模版2和模版3要小心处理边界访问。

