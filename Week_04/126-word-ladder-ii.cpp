class Solution {
public:
    
    bool check(string& a, string& b) {
        int count = 0;
        for(int i=0; i<a.size(); i++) {
            if (a[i] != b[i]) count++;
            if (count == 2) return false;
        }
        return true;
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        
        wordList.push_back(beginWord);
        int n = wordList.size();
        vector<bool> vis(n,0);
        vector<vector<int>> adj(n);
        vector<vector<string>> res;
        
        for(int i=0; i<n; i++) 
            for (int j=i+1; j<n; j++) 
                if (check(wordList[i], wordList[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }

        queue<vector<int>> q;
        q.push({n-1});
        vis[n-1] = 1;
        bool found = 0;
        while (!q.empty() && !found) {
            int sz = q.size();
            for(int i=0; i<sz; i++) {
                
                auto path = q.front(); q.pop();
                
                vis[path.back()] = 1;
                for(int child: adj[path.back()]) {
                    if (vis[child]) continue;
                    auto temp = path;
                    temp.push_back(child);
                    q.push(temp);
                    if (wordList[child] == endWord)  {
                        vector<string> str;
                        for(int i: temp) str.push_back(wordList[i]);
                        res.push_back(str);
                        found = 1;
                    }
                }
            }
        }
        
        return res;
    }
};
