class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;
        priority_queue<pair<int, int>> maxHeap; // 大顶堆

        for (int n : nums) {
            hashMap[n]++;
        }

        vector<int> ans;
        for (auto it = hashMap.begin(); it != hashMap.end(); it++) {
            maxHeap.push(make_pair(it->second, it->first));
            // 队列里最多只放hashMap.size() - k 个元素，也是从hashMap.size()中选出k个元素
            if (maxHeap.size() > hashMap.size() - k) {
                ans.push_back(maxHeap.top().second);
                maxHeap.pop();
            }
        }

        return ans;
    }
    
};
