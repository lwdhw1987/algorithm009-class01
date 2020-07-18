# 字符串与DP实战总结
### 子问题划分
以[44.通配符匹配为例](https://leetcode-cn.com/problems/wildcard-matching/)
dp[i][j]代表s[0:i]是否能被p[0:j]匹配。

问题首先划分成p[j-1]等于'\*'和不等于'\*'两种情况:

1.当p[j-1]不等于'\*'，且p[j-1]与s[i-1]可以匹配，那么dp[i][j]取决于s[0:i-2]是否能被p[0:j-2]匹配

2.当p[j-1]等于'\*':
  
    -2.1: '*'可以匹配任意字符串, 如果匹配当前字符s[i-1], 那dp[i][j]将取决于s[0:i-2]是否能被p[0:j-1]匹配(dp[i-1][j])
    
    -2.2: 如果不匹配当前字符, dp[i][j]将取决于s[0:i-1]是否能被p[0:j-2]匹配

```cpp
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
```

再以[115.不同的子序列为例](https://leetcode-cn.com/problems/distinct-subsequences/)



```cpp
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
```

### 初始化定义
