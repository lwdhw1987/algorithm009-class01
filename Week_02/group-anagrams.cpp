class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 给每个单词编码，互为异位词的key值相同
        map<string, vector<string>> dict;
        for (int i = 0; i < strs.size(); i++) {
            string key = strs[i];
            sort(key.begin(), key.end());
            dict[key].push_back(strs[i]);
        }

        vector<vector<string>> ans;
        for (auto it = dict.begin(); it != dict.end(); it++) {
            ans.push_back(it->second);
        }

        return ans;
    }
};
