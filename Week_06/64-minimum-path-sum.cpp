class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp = grid;
        int m = dp.size();
        int n = dp[0].size();

        for (int i = 1; i < m; i++) {
            dp[i][0] += dp[i-1][0];
        }

        for (int j = 1; j < n; j++) {
            dp[0][j] += dp[0][j-1];
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }

        return dp[m-1][n-1];
    }
};
