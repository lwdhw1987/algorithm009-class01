class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<int> dp(m, 0);

        for (int j = 0; j < m; j++) {
            if (obstacleGrid[0][j]) {
                dp[j] = 0;
                break;
            }
            dp[j] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (obstacleGrid[i][j]) {
                    dp[j] = 0;
                }
                else if (j > 0){
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[m - 1];
    }
};
