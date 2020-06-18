class Solution {
public:
    bool canJump(vector<int>& nums) {
        int next = 0;
        for (int i = 0; i < nums.size() && i <= next; i++) {
            next = max(next, i + nums[i]);
            if (next >= nums.size() - 1) break;
        }
        return next >= nums.size() - 1;
    }
};
