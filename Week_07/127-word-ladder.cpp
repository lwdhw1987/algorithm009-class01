/*
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 预处理
        unordered_map<string, vector<int>> common;
        wordList.push_back(beginWord);
        for (int i = 0; i < wordList.size(); i++) {
            for (int j = 0; j < wordList[i].size(); j++) {
                string t = wordList[i];
                t[j] = '*';
                common[t].push_back(i);
            }
        }

        // BFS访问
        int ans = 1;
        vector<bool> visitied(wordList.size() + 1, false); // 禁止重复访问
        queue<int> fifo;
        fifo.push(wordList.size() - 1);
        visitied[wordList.size() - 1] = true;
        while (!fifo.empty()) {
            int size = fifo.size();
            for (int k = 0; k < size; k++) {
                string word = wordList[fifo.front()];
                if (word == endWord) return ans;
                fifo.pop();
                for (int i = 0; i < word.size(); i++) {
                    string t = word;
                    t[i] = '*';
                    // 遍历距离为1并存在于字典的单词
                    for (int j : common[t]) {
                        if (!visitied[j]) {
                            // cout << wordList[j] << endl;
                            fifo.push(j);
                            visitied[j] = true;
                        }
                    }
                }
            }
            ans++;
        }

        // 返回结果
        return 0;
    }
};
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.push_back(beginWord);
        unordered_set<string> wordListSet(wordList.begin(), wordList.end());
        int endWordFound = false;
        for (string s : wordList) {
            if (s == endWord) endWordFound = true;
        }

        if (!endWordFound) {
            return 0;
        }
        
        // 分别以源和目的为起点，创建两个Set，用于保存各自BFS中间结果
        queue<string> fromSrc;
        queue<string> fromDst;
        unordered_set<string> visitedFromSrc;
        unordered_set<string> visitedFromDst;
        fromSrc.push(beginWord);
        fromDst.push(endWord);
        visitedFromSrc.insert(beginWord);
        visitedFromDst.insert(endWord);

        // 开始双向BFS，每次距离+1，从源出发遍历到节点a，从目的出发遍历到节点b
        int length = 1;
        while (!fromSrc.empty() && !fromDst.empty()) {
            // 双向BFS每次遍历，选择节点数较小的一路
            queue<string>& bfs = fromSrc.size() < fromDst.size() ? fromSrc : fromDst;
            unordered_set<string>& visited = fromSrc.size() < fromDst.size() ? visitedFromSrc : visitedFromDst;
            int size = bfs.size();
            for (int i = 0; i < size; i++) {
                string s = bfs.front();
                bfs.pop();
                for (int i = 0; i < s.size(); i++) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        string ss = s;
                        ss[i] = c;
                        if (!visited.count(ss) && wordListSet.count(ss)) {
                            // 如果当前节点存在于另一个Set中，代表相遇的最短路径
                            if (visitedFromSrc.count(ss) || visitedFromDst.count(ss)) {
                                return length + 1;
                            }
                            bfs.push(ss);
                            visited.insert(ss);
                        }
                    }
                }
            }
            length++;
        }
        
        return 0;
    }
};
