# 从背包问题入门动态规划
(文中图片引用自[算法图解](https://book.douban.com/subject/26979890//))
### 问题定义
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/define_problem.png" width = "800" height = "500">

有三种商品，有两个属性分别是**价值**和**重量**，给定背包的**最大容量Capacity**，背包所能装的商品最大价值是多少?

### 子问题拆解
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/sub_problem.png" width = "300" height = "200">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/matrix.png" width = "500" height = "400">

**将问题拆分成子问题:** 分成两个维度来看待，第一个维度代表**商品的种类i**，第二个维度代表**背包的容量j**(1到Capacity)，这两个维度组成了一个二维矩阵，
矩阵中的每个坐标代表了在**背包容量为j**时，在**商品0到商品i**中，能装入商品的**最大价值**，定义为**dp[i][j]**。

### 解决子问题
#### 吉他
只有一种商品，且吉他的重量为1磅，所以哪一种背包容量都可以装下，且能装下的最大价值都是$1500。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/gitar.png" width = "300" height = "200">

#### 音响
音响的重量是4磅，所以只有背包容量为4时才放的下，这时有两种选择**放入音响**和**不放音响**，如果不放则背包的最大价值还是dp[i-1][j]。如果放入，
那么音响会占满背包空间，无法再放入其他商品，此时的背包内的最大价值就是音响价值$3000。
当背包容量小于4时，dp[i][j]保持dp[i-1][j]的状态不变。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/laptop1.png" width = "300" height = "200">

#### 笔记本电脑
笔记本的重量是3磅，当背包容量小于2时，dp[i][j]保持dp[i-1][j]的状态不变。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/laptop2.png" width = "300" height = "200">

当背包容量为3时，可以选择**放入笔记本电脑**或**不放**，如果不放则背包的最大价值还是dp[i-1][j]，否则，笔记本的重量占满背包空间，此时背包的最大价值
是笔记本电脑的价值$2000

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/laptop2.png" width = "300" height = "200">

同样，当背包容量为4时，如果不放则背包的最大价值还是dp[i-1][j]，否则选择放入笔记本电脑，背包还剩余1磅的空间，而之前求解过dp[i][1]，就是当背包容量为1磅
时，能够放入的最大价值是吉他$1500，加上放下的笔记本电脑，总共$3500。至此，得到了背包问题的最终解。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/laptop3.png" width = "300" height = "200">

而上述求解过程完全可以公式化，如下：
这里的cell[i][j]就是dp[i][j]，并且需要注意，只有当背包容量j > 当前商品的重量，剩余空间的价值才有意义，换个说法就是此时只能选择不放当前商品，背包内
能放入的最大价值就是dp[i-1][j]。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/fomula.png" width = "700" height = "200">

### 总结
使用动态规划拆解子问题时，子问题的解一定要具备**相互独立性**和**完备性**，简单讲就是**互补**，并且子问题可以**继续拆分**，例如上述解法中，dp[i][j]对应
的位置，**放入商品i**和**不放入商品i**就是相互独立且互补的，而这两种独立的解合并就是整个问题的解。两个独立子问题可以进一步拆分成dp[i-1][j]或者
dp[i][j - weight] + value[i]。而子问题的拆分有多种方式，需要经验和大量练习才能灵活运用。





