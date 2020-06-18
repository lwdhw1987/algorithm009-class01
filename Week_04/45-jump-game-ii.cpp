class Solution {
public:
    int jump(vector<int>& nums) {
        // 1、先寻找本次跳跃的边界，也就是说边界内必有一次跳跃
        // 2、在边界内寻找跳跃能力最强者，其跳跃距离就是下一个边界
        // 3、在边界处更新跳跃次数与下个边界
        int step = 0;
        int border = 0;
        int max_jump = 0;
        
        // i < nums.size() - 1避免在终点更新跳跃次数
        for (int i = 0; i < nums.size() - 1; i++) {
            max_jump = max(max_jump, nums[i] + i);
            if (i == border) {
                step++;
                border = max_jump;
            }
        }

        return step;
    }
};

class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int i = 0;
        int step = 0;
        while (i < nums.size() - 1) {
            int next = 0;
            int max_num = 0;
            // 遍历每个节点，寻找能力范围内的下一个节点，且下个节点依然满足能力最大化
            for (int j = i + 1; j <= i + nums[i] && j < nums.size(); j++) {
                if (nums[j] + j > max_num || j == nums.size() - 1) {
                    next = j;
                    max_num = nums[j] + j;
                }
            }
            i = next;
            step++;
        }

        return step;
    }
};

