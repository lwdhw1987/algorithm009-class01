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
下图所示插入节点(2, T)的过程，从叶子结点开始，重复与父节点的比较和替换过程，最终还原了有序性，将key值最小的(2, T)交换到了根节点，这个过程叫做up-heap bubbling。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/up-bubbling1.png?raw=true" width = "600" height = "400">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/up-bubbling2.png?raw=true" width = "600" height = "400">

### 删除元素
```java
public E poll() {
	if (size == 0)
		return null;
	int s = --size;
	modCount++;
	E result = (E) queue[0];
	E x = (E) queue[s];
	queue[s] = null;
	if (s != 0)
		siftDown(0, x);
	return result;
}
```
每次删除根节点的数据，此时破坏了**完全二叉树**的完整性，解决办法是将最后一个元素放到根节点上，并将末尾节点设置成null，然后调用**siftDown**方法和底层的**siftDownComparable**方法，从根节点开始，判断父节点和较小子节点的大小，如果父节点大于子节点就进行交换，直到父节点小于子节点或者到达叶子节点的位置。
```java
private void siftDownComparable(int k, E x) {
	Comparable<? super E> key = (Comparable<? super E>) x;
	int half = size >>> 1;        // loop while a non-leaf
	while (k < half) {
		int child = (k << 1) + 1; // assume left child is least
		Object c = queue[child];
		int right = child + 1;
		if (right < size &&
				((Comparable<? super E>) c).compareTo((E) queue[right]) > 0)
			c = queue[child = right];
		if (key.compareTo((E) c) <= 0)
			break;
		queue[k] = c;
		k = child;
	}
	queue[k] = key;
}
```
下图所示删除节点的过程，从heap根节点获取要删除的元素，将heap最后一个节点拷贝到根节点的位置，并将原来的叶子结点设置为null，然后重复比较父节点和较小子节点的值，进行置换。完成后heap的根节点将是所有节点中key值最小的。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/down-bubbling1.png?raw=true" width = "600" height = "400">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/down-bubbling2.png?raw=true" width = "600" height = "400">

### 时间复杂度
查询最小值的时间复杂度为O(1)，添加元素或删除最小值的时间复杂度为O(logn)

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_01/complexity.png?raw=true" width = "400" height = "200">

