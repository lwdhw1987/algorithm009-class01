class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int p = 0;
        for (int n : nums) {
            if (!p || n > nums[p-1]) {
                nums[p++] = n;
            }
        }

        return p;
    }
};