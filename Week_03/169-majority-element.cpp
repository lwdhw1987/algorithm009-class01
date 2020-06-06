class Solution {
public:
    int helper(vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }

        int mid = left + (right - left) / 2;
        int leftMojority = helper(nums, left, mid);
        int rightMojority = helper(nums, mid + 1, right);
        if (leftMojority == rightMojority) {
            return leftMojority;
        }

        int a = count(nums.begin() + left, nums.begin() + right + 1, leftMojority);
        int b = count(nums.begin() + left, nums.begin() + right + 1, rightMojority);
        return (a > b ? leftMojority : rightMojority);
    }

    int majorityElement(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }
};
