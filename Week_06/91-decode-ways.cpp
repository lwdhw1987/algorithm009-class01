/*
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        int dp[n+1];
        if (s[0] == '0') {
            return 0;
        }

        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (s[i-1] == '0') {
                if (s[i-2] == '1' || s[i-2] == '2') {
                    dp[i] = dp[i-2];
                }
                else {
                    return 0;
                }
            }
            else if (s[i-2] == '1' || (s[i-2] == '2' && s[i-1] <= '6' && s[i-1] >= '1')) {
                dp[i] = dp[i-1] + dp[i-2];
            }
            else {
                dp[i] = dp[i-1];
            }
        }

        return dp[n];
    }
};
*/
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if (s[0] == '0') {
            return 0;
        }
        // dp_i, [0, i]范围内解码方法总数
        // dp_i_1, dp[i-1]
        // dp_i_2, dp[i-2]
        int dp_i_2 = 1;
        int dp_i_1 = 1;
        int dp_i = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == '0') {
                if (s[i-1] == '1' || s[i-1] == '2') {
                    dp_i = dp_i_2;
                }
                else {
                    return 0;
                }
            }
            else if (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6' && s[i] >= '1')) {
                dp_i = dp_i_1 + dp_i_2;
            }
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }
};
