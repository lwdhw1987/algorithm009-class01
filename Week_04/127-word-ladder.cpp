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
