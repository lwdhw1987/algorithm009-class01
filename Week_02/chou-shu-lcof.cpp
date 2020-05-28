class Solution {
public:
    int nthUglyNumber(int n) {
        // 维护一个小顶堆
        priority_queue<double, vector<double>, greater<double> > minHeap; 
        unordered_set<double> log;
        minHeap.push(1);
        int ans;
        while (n--) {
            int factor[3] = {2, 3, 5};
            for (int i = 0; i < 3; i++) {
                double num = minHeap.top() * factor[i];
                if (log.find(num) == log.end()) {
                    minHeap.push(num);
                    log.insert(num);
                    // cout << num << " ";
                }
            }
            if (n == 0) ans = minHeap.top();
            minHeap.pop();
        }

        return ans;

    }
};
