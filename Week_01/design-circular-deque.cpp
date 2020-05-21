class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        storage = new int[k];
        capacity = k;
        full = false;
        head = 0;
        tail = 0;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) return false;
        storage[tail] = value;
        tail = (tail + 1) % capacity;
        if (head == tail) full = true;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        head = (head + 1) % capacity;
        if (full) full = false;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) return -1;
        return storage[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) return -1;
        return storage[(tail + capacity - 1) % capacity];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        if (!full && head == tail) return true;
        return false;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return full;
    }

private:
    int* storage;
    int capacity;
    int head;
    int tail;
    bool full;
};