class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        vector<vector<int>> dp(len, vector<int>(len, false));
        int start = 0;
        int end = 0;

        for (int j = 0; j < len; j++) {
            for (int i = 0; i <= j; i++) {
                // 判断两种情况：1、子串长度大于3且两头字符相等，且中间子串是回文串
                // 2、子串长度小于等于2，且两头字符相等
                if (s[i] == s[j] && ((i + 1 > j - 1) || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    if (j - i > end - start) {
                        start = i;
                        end = j;
                    }
                }
            }
        }

        return s.substr(start, end - start + 1);
    }
};
