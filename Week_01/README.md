# 个人总结-Priority Queue源码分析
本文源码来自[jdk8](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/687fd7c7986d/src/share/classes/java/util/PriorityQueue.java)

### Priority Queue内部数据结构
java中的priority queue基于priority heap实现，heap也是一个**完全二叉树**，并且heap的根节点是按照某种规则排序的最值。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/heap.png?raw=true" width = "600" height = "400">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/array.png?raw=true" width = "600" height = "100">

如上图所示，heap根节点对应于数组索引p = 0，然后从根节点开始作为父节点，left children和right children对应于数组的索引分别是2 * p + 1和2 * p + 2。

### 构造函数
```java
public PriorityQueue(int initialCapacity,
                     Comparator<? super E> comparator) {
    // Note: This restriction of at least one is not actually needed,
    // but continues for 1.5 compatibility
	if (initialCapacity < 1)
        throw new IllegalArgumentException();
	this.queue = new Object[initialCapacity];
    this.comparator = comparator;
}
```

用数组存储每个元素，并且可以通过用户自定义的comparator实现各种排序规则。

### 添加元素
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/up-bubbling1.png?raw=true" width = "600" height = "400">


