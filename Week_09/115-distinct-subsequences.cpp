class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<vector<long>>dp(n+1, vector<long>(m+1, 0));
        dp[0][0] = true;
        // 空字符串是s的子序列
        for (int i = 1; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (t[j-1] == s[i-1]) {
                    // dp[i-1][j-1], 将s[i-1]算在内，去s[0:i-2]中寻找t[0:i-2]出现次数
                    // dp[i-1][j], 不算s[i-1]，去s[0:i-2]中寻找t[0:i-1]出现次数
                    // 例如 s = "###g##g", t = "bag"
                    // 包含最后一个g, 只需要在“###g##”中统计“ba”出现的次数
                    // 再加上不含最后一个g, 在“###g##”中统计"bag"出现的次数
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[n][m];
    }
};
