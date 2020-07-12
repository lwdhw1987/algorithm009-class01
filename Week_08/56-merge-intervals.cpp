class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 先按照左端点排序，再依次两两合并
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); i++) {
            int left = intervals[i][0];
            int right = intervals[i][1];
            if (merged.empty() || merged.back()[1] < left) {
                merged.push_back(intervals[i]);
            }
            else {
                merged.back()[1] = max(merged.back()[1], right);
            }
        }

        return merged;
    }
};
