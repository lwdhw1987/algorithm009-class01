class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;
        // 匹配空字符串
        for (int i = 1; i <= p.size(); i++) {
            if (p[i-1] != '*') {
                break;
            }
            dp[0][i] = true;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j-1] == '*') {
                    // dp[i-1][j], *匹配s[i-1]
                    // dp[i][j-1], *不匹配s[i-1]
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                }
                else if (p[j-1] == '?' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        
        return dp[n][m];
    }
};
