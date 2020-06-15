class Solution {
public:
    int findMin(vector<int>& nums) {
        if (!nums.empty() && nums.back() >= nums[0]) return nums[0];
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (mid > 0 && nums[mid] < nums[mid - 1]) {
                return nums[mid];
            }

            if (nums[mid] >= nums[0]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        
        return nums[left];
    }
};
