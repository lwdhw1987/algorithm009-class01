class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        // dp[i]到i为止，包含有效括号的最长子串长度
        int ans = 0;
        for (int i = 1; i < n; i++) {
            // 场景1: ...()
            if (s[i] == ')' && s[i-1] == '(') {
                dp[i] = i - 2 >= 0 ? dp[i-2] + 2 : 2; 
            }
            // 场景2: ...((...))
            else if (s[i] == ')' && s[i-1] == ')' && dp[i-1] > 0) {
                if (i - dp[i-1] - 1 >= 0 && s[i - dp[i-1] - 1] == '(') {
                    dp[i] = dp[i-1] + 2;
                    if (i - dp[i-1] - 2 >= 0) {
                        dp[i] += dp[i - dp[i-1] - 2];
                    }
                }
            }
            
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};
