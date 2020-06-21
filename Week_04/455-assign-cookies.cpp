class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 用最小的饼干满足胃口最小的孩子
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int satisfy = 0;
        int i = 0;
        int j = 0;

        while (i < s.size() && j < g.size()) {
            if (s[i] >= g[j]) {
                j++;
                satisfy++;
            }
            i++;
        }

        return satisfy;
    }
};
