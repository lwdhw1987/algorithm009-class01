class Solution {
public:
    void helper(vector<int> nums, vector<vector<int>>& ans, int start) {
        if (start == nums.size()) {
            ans.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[start]) {
                continue;
            }
            swap(nums[start], nums[i]);
            helper(nums, ans, start + 1);   
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int> > ans;
        // 相同的值相邻
        sort(nums.begin(), nums.end());
        helper(nums, ans, 0);
        return ans;
    }
};
