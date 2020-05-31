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
先看***separate chaining***，HashTable的每个索引对应位置的bucket存放的是一个单链表，当***hash function***对key的计算比较均匀，单链表的平均长度k = load factor = n / N。HashTable插入数据的时间复杂度为O(1)，查找或删除操作的时间复杂度为o(k)。如果用更高效的动态数据结构比如**红黑树**、**跳表**代替单链表，那么查找和删除操作的时间复杂度可以进一步优化为O(log(n))。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/separate_chaining.png?raw=true" width = "500" height = "250">

再看***open addressing***，最基本的处理方法是**线性探测**，插入一个数据时，从key对应的索引位置开始向后探测，遇到的第一个空闲位置，就是插入map元素的位置。当loader factor比较大时，代表HashTable空闲位置很小，**线性探测**很慢，最坏情况下要探测整个HashTable，插入、查找和删除的时间复杂度为o(n)。经典的探测算法还包括**quadratic probing**和**double hashing**，同样的，当HashTable空闲位置不多的时候，Hash冲突的概率会大大提高。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_02/linear_probing.png?raw=true" width = "500" height = "150">

**open addressing**的优点是HashTable中的数据都保存在数组中，可以有效地利用cpu缓存加快查询速度，做序列化时也更加简单。缺点是删除数据时比较麻烦，需要对删除过的位置特殊标记，另外loader factor不能太大，否则处理冲突的代价太大。

***separate chaining***的优点是对内存的利用率较高，因为不需要事先分配内存空间，需要用的时候再申请。同时对较大的loader factor容忍度比较好。缺点是对于size比较小的存储对象，由于链表还要存储指针，内存占用的性价比不高。而且链表中结点在内存中的地址是不连续的，对cpu缓存执行效率有一定影响。

所以，**当数据量比较小，loader factor比较小的情况下，适合采用open addressing，例如java中的ThreadLocalMap**。
**而基于单链表的冲突处理方法，适合存储大size对象、大数据量的HashTable，支持多种优化策略，例如红黑树优化**

### 动态扩容
***loader factor***越大，HashTable中空闲位置越少，冲突概率越大。当HashTable的***loader factor***高于某个值，启动动态扩容，将HashTable的容量翻倍，重新计算HashTable索引，并且搬移数据，用摊还分析法分析，动态扩容的复杂度为O(1)。为了解决一次行扩容耗时多的情况，可以先扩容而不搬移数据，每次插入一个新数据的时候再搬移一个旧数据，这样将一次性的数据搬移分摊到每次新数据的插入过程里，在任何时刻，插入数据的时间复杂度都是O(1)。

### Java中的HashMap实现
#### 构造函数
```java
public HashMap(int initialCapacity, float loadFactor) {
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal initial capacity: " +
                                               initialCapacity);
        if (initialCapacity > MAXIMUM_CAPACITY)
            initialCapacity = MAXIMUM_CAPACITY;
        if (loadFactor <= 0 || Float.isNaN(loadFactor))
            throw new IllegalArgumentException("Illegal load factor: " +
                                               loadFactor);
        this.loadFactor = loadFactor;
        this.threshold = tableSizeFor(initialCapacity);
    }
}
```

#### 添加元素，键-值对
```java
final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                   boolean evict) {
        Node<K,V>[] tab; Node<K,V> p; int n, i;
        if ((tab = table) == null || (n = tab.length) == 0)
            // 当哈希表数组为 null 或者长度为 0 时，初始化哈希表数组
            n = (tab = resize()).length;
        if ((p = tab[i = (n - 1) & hash]) == null)
            // 没有出现哈希碰撞直接将新节点插入对应的桶内
            tab[i] = newNode(hash, key, value, null);
        // 哈希碰撞
        else {
            Node<K,V> e; K k;
            if (p.hash == hash &&
                ((k = p.key) == key || (key != null && key.equals(k))))
                e = p;
            else if (p instanceof TreeNode)
                // 如果是树节点，走树节点插入流程
                e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
            else {
                // 链表处理流程
                for (int binCount = 0; ; ++binCount) {
                    if ((e = p.next) == null) {
                        p.next = newNode(hash, key, value, null);
                        // 如果当前链表中的元素大于树化的阈值，进行链表转树的操作
                        if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                            treeifyBin(tab, hash);
                        break;
                    }
                    // 如果 key 已经存在，直接结束循环
                    if (e.hash == hash &&
                        ((k = e.key) == key || (key != null && key.equals(k))))
                        break;
                    p = e;
                }
            }
            // 如果 key 重复则更新 key 值
            if (e != null) { // existing mapping for key
                V oldValue = e.value;
                if (!onlyIfAbsent || oldValue == null)
                    e.value = value;
                afterNodeAccess(e);
                return oldValue;
            }
        }
        ++modCount;
        // 如果键值对个数大于阈值时（capacity * load factor），进行扩容操作
        if (++size > threshold)
            resize();
        afterNodeInsertion(evict);
        return null;
    }
```
HashMap底层采用单链表解决hash冲突，一旦链表超过一定长度，就会转换成红黑树。
```java
final void treeifyBin(Node<K,V>[] tab, int hash) {
        int n, index; Node<K,V> e;
        if (tab == null || (n = tab.length) < MIN_TREEIFY_CAPACITY)
            resize();
        else if ((e = tab[index = (n - 1) & hash]) != null) {
            TreeNode<K,V> hd = null, tl = null;
            do {
                TreeNode<K,V> p = replacementTreeNode(e, null);
                if (tl == null)
                    hd = p;
                else {
                    p.prev = tl;
                    tl.next = p;
                }
                tl = p;
            } while ((e = e.next) != null);
            if ((tab[index] = hd) != null)
                hd.treeify(tab);
        }
    }
		
 static final class TreeNode<K,V> extends LinkedHashMap.Entry<K,V> {
        TreeNode<K,V> parent;  // red-black tree links
        TreeNode<K,V> left;
        TreeNode<K,V> right;
        TreeNode<K,V> prev;    // needed to unlink next upon deletion
        boolean red;
        TreeNode(int hash, K key, V val, Node<K,V> next) {
            super(hash, key, val, next);
        }

        /**
         * Returns root of tree containing this node.
         */
        final TreeNode<K,V> root() {
            for (TreeNode<K,V> r = this, p;;) {
                if ((p = r.parent) == null)
                    return r;
                r = p;
            }
        }
```

对于***hash function***、**插入和删除、动态扩容**的具体代码分析参考[1](https://github.com/zchen96/jdk1.8-source-code-read/blob/master/notes/data-structure/HashMap.md)

