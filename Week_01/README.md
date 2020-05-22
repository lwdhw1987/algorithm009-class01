# Priority Queue源码分析
本文源码来自[jdk8](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/687fd7c7986d/src/share/classes/java/util/PriorityQueue.java)

### Priority Queue内部数据结构
java中的priority queue基于priority heap实现，heap也是一个**完全二叉树**，并且heap的根节点是按照某种规则排序的最值。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/heap.png?raw=true" width = "600" height = "544">
