class Solution {
public:
    // a表示列冲突，b表示对角线冲突，c表示反对角线冲突
    void put(int row, int n, vector<vector<string>>& ans, vector<string>& solve, 
            int a, int b, int c) {
        if (row == n) {
            // 保存解法
            ans.push_back(solve);
            return;
        }

        // 在当前行放置Queen, 有多种可能
        // 取反再取低n位，bit = 1表示有效位
        int valid = ~(a | b | c) & ((1 << n) - 1);
        while (valid) {
            // 只保留最低有效位
            int leftmost = valid & (-valid);
            int i = log2(leftmost);
            string s(n, '.');
            s[n - 1 - i] = 'Q';
            solve.push_back(s);
            // 去下一行放置Queen
            put(row + 1, n, ans, solve, a | leftmost, (b | leftmost) << 1, 
                (c | leftmost) >> 1);
            
            // 回溯，清除当前解，准备下一个
            solve.pop_back();
            // 清除最低有效位, 准备处理下一个
            valid = valid & (valid - 1);
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> solve;
        put(0, n, ans, solve, 0, 0, 0);
        return ans;
    }
};
