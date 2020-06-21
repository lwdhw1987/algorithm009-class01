class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for (int k = 0; k < n - 2; k++) {
            if (k > 0 && nums[k] == nums[k - 1])
            {
                continue;
            }
            
            for (int i = k + 1, j = n - 1; i < j;) {
                if (nums[k] > 0) {
                    break;
                }
                int s = nums[k] + nums[i] + nums[j];
                if (s > 0) j--;
                else if (s < 0) i++;
                else {
                    ans.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i+1]) i++;
                    while (i < j && nums[j] == nums[j-1]) j--;
                    i++; j--;
                }
            }
        }

        return ans; 
    }
};
