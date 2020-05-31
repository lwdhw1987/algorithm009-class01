# HashMap学习总结
本文源码来自[jdk8](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/classes/java/util/HashMap.java)

### 什么是Map
Map描述了一种映射关系，如下图所示，是一组的keys和一组values之间的映射，其中每一个key必须是唯一的，但是不同的key可以和同一个value映射，是多对1的关系。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/map.png?raw=true" width = "600" height = "150">

如下图所示，Map有多种实现方式，其中HashMap就是通过***hash function***将key和数组索引一一对应，并将构成Map的**键-值对**保存到HashTable中，以达到理想情况下查找、删除和添加操作O(1)的时间复杂度。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/map_types.png?raw=true" width = "500" height = "300">

### HashTable的原理
如下图所示，是一个能够容纳11个keys的Hash Table，里面存放了(1,D), (25,C), (3,F), (14,Z), (6,A), (39,C), 和(7,Q) 7个**键-值对**。
由于key值不一定是顺序的数组下标，而可以是任意字符或数字，所以需要用***hash function***将key值和Hash Table的索引index做映射。理想情况下，keys在[0, table size - 1]的范围内均匀分布，而实际情况是，有多个keys经过***hash function***映射，对应到table中同一个索引中，所以table可以抽象地看作一个***bucket array***，桶内可能存放多个**键-值对**。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/hash_table.png?raw=true" width = "500" height = "150">

如下图所示，***hash function***包含两个部分，***hash code***将key值映射为整数，***compression function***将***hash code***映射到范围[0, table size - 1]的***bucket array***。这样做的好处是方便设计一个与table size无关的通用***hash code***，这在后续的实现过程中非常方便，因为Hash Table的size会随着存放元素的个**数动态扩容**或缩减。对***hash function***设计有几点要求，首先是计算简便、快速，其次是能有效减小hash冲突。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/hash_function.png?raw=true" width = "500" height = "300">

### Hash冲突的解决方法
对于key1 != key2，如果hash(key1) == hash(key2)，就发生了hash冲突。解决hash冲突主要有2种方法，第一是***open addressing***，第二是***separate chaining***。

假设Map中有n个元素，HashTable key的容量为N，当load factor = n / N比较大时，HashTable更容易发生Hash冲突。
先看***separate chaining***，HashTable的每个索引对应位置的bucket存放的是一个单链表，当***hash function***对key的计算比较均匀，单链表的平均长度k = load factor = n / N。HashTable插入数据的时间复杂度为O(1)，查找或删除操作的时间复杂度为o(k)。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/separate_chaining.png?raw=true" width = "500" height = "250">

再看***open addressing***，最基本的处理方法是**线性探测**，

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/linear_probing.png?raw=true" width = "500" height = "150">




