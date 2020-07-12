class LRUCache {
public:
    LRUCache(int capacity) {
        cache_size = capacity;
    }

    void move_to_front(int key, int value) {
        list<Node>::iterator it = dict[key];
        it->v = value;
        cache.splice(cache.begin(), cache, it);
    }
    
    int get(int key) {
        if (dict.find(key) == dict.end()) {
            return -1;
        }

        int value = dict[key]->v;
        move_to_front(key, value);

        return value;
    }
    
    void put(int key, int value) {
        if (dict.find(key) == dict.end()) {
            Node node;
            node.k = key;
            node.v = value;
            if (cache.size() == cache_size) {
                dict.erase(cache.back().k);
                cache.pop_back();
            } 
            cache.push_front(node);
            dict[key] = cache.begin();
        }
        else {
            move_to_front(key, value);
        }
    }

private:
    struct Node {
        int k;
        int v;
    };
    list<Node> cache;
    int cache_size;
    unordered_map<int, list<Node>::iterator> dict;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
