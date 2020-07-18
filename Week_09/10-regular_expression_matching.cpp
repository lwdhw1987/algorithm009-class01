class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        // dp[i][j]代表正则表达式p[0,j]是否匹配字符串[0, i]
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        // 空字符串和空正则表达式匹配，空正则表达式和非空字符都不匹配
        dp[0][0] = true; 
        // 非空正则表达式和空字符串匹配，正则表达式必然符合"#*#*#*"的规律
        for (int i = 2; i <= p.size(); i++) {
            if (p[i-1] == '*' && dp[0][i-2]) {
                dp[0][i] = true;
            }
        }

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= p.size(); j++) {
                if (p[j-1] == '*') {
                    // dp[i][j-1], *匹配一个，例如p = "ab*",  s = "ab"
                    // dp[i][j-2], *匹配零个，例如p = "abb*", s = "ab" 
                    // dp[i-1][j], *匹配多个，例如p = "ab*",  s = "abbbb"
                    if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                        dp[i][j] = dp[i][j-1] || dp[i][j-2] || dp[i-1][j];
                    }
                    else {
                        dp[i][j] = dp[i][j-2];
                    }
                }
                else if (p[j-1] == '.' || s[i-1] == p[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }

        return dp[n][m];
    }
};
