# HashMap学习总结
本文源码来自[jdk8](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/classes/java/util/HashMap.java)

### HashTable的原理
如下图所示，是一个能够容纳11个keys的Hash Table，里面存放了(1,D), (25,C), (3,F), (14,Z), (6,A), (39,C), 和(7,Q) 7个**键-值对**。
由于key值不一定是顺序的数组下标，而可以是任意字符或数字，所以需要用***hash function***将key值和Hash Table的索引index做映射。理想情况下，keys在[0, table size - 1]的范围内均匀分布，而实际情况是，有多个keys经过***hash function***映射，对应到table中同一个索引中，所以table可以抽象地看作一个***bucket array***，桶内可能存放多个**键-值对**。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/hash_table.png?raw=true" width = "500" height = "150">

如下图所示，***hash function***包含两个部分，***hash code***将key值映射为整数，***compression function***将hash code映射到范围[0, table size - 1]的***bucket array***。这样做的好处是方便设计一个与table size无关的通用***hash code***，这在后续的实现过程中非常方便，因为Hash Table的size会随着存放元素的个数不断变化。对***hash function***设计有几点要求，首先是计算简便、快速，其次是能有效减小hash冲突。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/hash_function.png?raw=true" width = "500" height = "300">
