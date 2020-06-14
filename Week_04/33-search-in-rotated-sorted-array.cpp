class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            
            // 根据mid和left关系判断左右分段哪个有序
            // 也可以根据nums[mid-1]来判断，但是要增加索引mid - 1的合法性判断
            // 用mid在代码实现上更简单
            if (nums[mid] >= nums[left]) {
                // 根据target与边界的关系判断taget在哪个分段
                if (target < nums[mid] && target >= nums[left]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};
