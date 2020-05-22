class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int count = 0;
        for (int start = 0; count < nums.size(); start++) {
            int cur = start;
            int pre = nums[cur];
            do {
                int next = (cur + k) % nums.size();
                int temp = nums[next];
                nums[next] = pre;
                cur = next;
                pre = temp;
                count++;
            } while(cur != start);
        }
    }
};