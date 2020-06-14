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
模版2代码采用左闭右开的的表示方式，查找区间表示为[L, R)，划分子问题后，左右区间分别为[L, mid), [mid + 1, R)。**查找过程只能接触到左边界**, 当查找区间的长度为2，且nums[mid] != target，查找子区间变为[R, R)或者[L, L)，此时已经满足递归结束条件，但是仍要判断nums[R] == target或者nums[L] == target。

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

总结，从二分查找过程对左右边界的访问可以分成三种模版，对应不同的代码需求。对于模版2和模版3要小心处理边界访问。

### 回溯与递归
从n皇后问题学习递归与回溯，递归函数包含4个要素：
1. 结束条件
2. 计算逻辑
3. 进入下一层计算，保存计算结果
4. 回溯阶段，清除当前状态，为下一次计算做准备

看n皇后问题的递归解：
```cpp
class Solution {
public:
    // a表示列冲突，b表示对角线冲突，c表示反对角线冲突
    void put(int row, int n, vector<vector<string>>& ans, vector<string>& solve, 
            int a, int b, int c) {
        if (row == n) {
            // 保存解法
            ans.push_back(solve);
            return;
        }

        // 在当前行放置Queen, 有多种可能
        // 取反再取低n位，bit = 1表示有效位
        int valid = ~(a | b | c) & ((1 << n) - 1);
        while (valid) {
            // 只保留最低有效位
            int leftmost = valid & (-valid);
            int i = log2(leftmost);
            string s(n, '.');
            s[n - 1 - i] = 'Q';
            solve.push_back(s);
            // 去下一行放置Queen
            put(row + 1, n, ans, solve, a | leftmost, (b | leftmost) << 1, 
                (c | leftmost) >> 1);
            
            // 回溯，清除当前解，准备下一个
            solve.pop_back();
            // 清除最低有效位, 准备处理下一个
            valid = valid & (valid - 1);
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> solve;
        put(0, n, ans, solve, 0, 0, 0);
        return ans;
    }
};
```

参数`vector<string>& solve`用于保存中间状态，参数`vector<vector<string>>& ans`用于保存最终解。递归是一层一层深入的，每一层都要暂存中间状态，直到递归触底返回，这里的触底就是满足递归结束条件。下图是一个递归执行过程的示意图：
  
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_03/recursion.jpeg" width = "500" height = "500">
  
递归从1开始，然后到2，再到3，层层深入，每一层都可能有多个中间状态，比如状态2、6、8或者3、4、5都是某一层的中间状态，当满足递归条件时，需要把当前的所有中间状态保存到最终解ans里，在n皇后问题中就对应着每一层放置Queen的方法。然后逐层将中间状态清除，比如1、2、3是一个解，然后清除中间状态3，回溯到中间状态2，然后再递归到中间状态4，如果又满足条件，就保存到最终解。当所有中间状态都遍历完成后，整个递归的中间状态都会清空。而所需答案都保存在最终解ans里。在代码中所有中间状态都是以引用参数的形式`vector<string>& solve`逐层传递下去的，因此需要开发者自己清除中间状态，这样的好处是节省内存，避免申请过多的临时变量。如果采用传值参数`vector<string> solve`的方式，当本层递归结束时，开发者不用自己清除中间状态，但要在本层内不同中间状态之间进行替换，且函数参数申请了额外的临时缓存。
  
  
  
  



