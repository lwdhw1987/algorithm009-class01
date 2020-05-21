class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        // 寻找有效的起始位置
        int left_bound = 0;
        while (left_bound < height.size() && height[left_bound] == 0) {
            left_bound++;
        }

        stack<int> walls;
        int area = 0;
        for (int i = left_bound; i < height.size(); i++) {
            // 右侧有高墙
            while (!walls.empty() && height[i] >= height[walls.top()]) {
                int k = walls.top();
                walls.pop();
                // 左侧有高墙，可以接雨水
                if (!walls.empty()) {
                    int h = min(height[i], height[walls.top()]) - height[k];
                    area += h * (i - walls.top() - 1);
                    // cout << area << endl;
                }
            }
            walls.push(i);
        }

        return area;
    }
};