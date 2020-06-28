# 从背包问题入门动态规划
(文中图片引用自[算法图解](https://book.douban.com/subject/26979890//))
### 问题定义
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/define_problem.png" width = "800" height = "500">

有三种商品，有两个属性分别是**价值**和**重量**，给定背包的**最大容量Capacity**，背包所能装的商品最大价值是多少?

### 子问题拆解
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/sub_problem.png" width = "300" height = "200">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/matrix.png" width = "500" height = "400">

**将问题拆分成子问题:** 分成两个维度来看待，第一个维度代表**商品的种类i**，第二个维度代表**背包的容量j**(1到Capacity)，这两个维度组成了一个二维矩阵，
矩阵中的每个坐标代表了在**背包容量为j**时，在**商品0到商品i**中，能装入商品的最大价值。

### 解决子问题
##### 吉他

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_06/gitar.png" width = "300" height = "200">
