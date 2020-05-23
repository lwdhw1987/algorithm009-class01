# 个人总结-Priority Queue源码分析
本文源码来自[jdk8](http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/687fd7c7986d/src/share/classes/java/util/PriorityQueue.java)

### Priority Queue内部数据结构
java中的priority queue基于priority heap实现，heap也是一个有序的**完全二叉树**，并且heap的根节点是按照某种规则排序的最值。

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
```java
public boolean offer(E e) {
	if (e == null)
		throw new NullPointerException();
	modCount++;
	int i = size;
	if (i >= queue.length)
		grow(i + 1);
	size = i + 1;
	if (i == 0)
		queue[0] = e;
	else
		siftUp(i, e);
	return true;
}
```
当插入元素个数超过了内部数组空间时，需要对数组扩容
```java
private void grow(int minCapacity) {
	int oldCapacity = queue.length;
	// Double size if small; else grow by 50%
	int newCapacity = oldCapacity + ((oldCapacity < 64) ?
									 (oldCapacity + 2) :
									 (oldCapacity >> 1));
	// overflow-conscious code
	if (newCapacity - MAX_ARRAY_SIZE > 0)
		newCapacity = hugeCapacity(minCapacity);
	queue = Arrays.copyOf(queue, newCapacity);
}
```
当之前的容量小于64时，扩容至原来的2倍+2，否则扩容至原来的1.5倍
接着，在heap的叶子结点插入新数据，此时会破坏有序的**完全二叉树**，因此需要依次将新插入的结点数据和父节点比较，在使用默认comparator的情况下，当新插入的结点小于父节点，则交换两者的位置，直到新结点大于其父节点，或者新结点被交换到根节点。这个过程是通过**siftUpComparable**方法实现的。
```java
private void siftUpComparable(int k, E x) {
	Comparable<? super E> key = (Comparable<? super E>) x;
	while (k > 0) {
		int parent = (k - 1) >>> 1;
		Object e = queue[parent];
		if (key.compareTo((E) e) >= 0)
			break;
		queue[k] = e;
		k = parent;
	}
	queue[k] = key;
}
```

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/up-bubbling1.png?raw=true" width = "600" height = "400">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/up-bubbling2.png?raw=true" width = "600" height = "400">


