struct TrieNode {
    bool isWord;
    //  不得不使用指针
    unordered_map<char, TrieNode*> next;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        // 遍历word，找到或插入新的节点，到最后一个字母，该节点isWord = true
        TrieNode* p = root;
        for (char c : word) {
            if (p->next[c] == nullptr) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
        }
        p->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        // 遍历word，如果字母对应的是空节点或到该节点为止不是有效单词，返回false
        TrieNode* p = root;
        for (char c : word) {
            if (p->next[c] == nullptr) {
                return false;
            }
            p = p->next[c];
        }
        return p->isWord ? true : false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        // 遍历prefix，如果字母对应的是空节点，返回false
        TrieNode* p = root;
        for (char c : prefix) {
            if (p->next[c] == nullptr) {
                return false;
            }
            p = p->next[c];
        }

        return true;
    }

private:
    TrieNode* root;
    
};

class Solution {
public:
    void helper(vector<vector<char>>& board, int row, int col, 
                    unordered_set<string>& unique, string s) {
        int m = board.size();
        int n = board[0].size();
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] == '#') {
            return;
        }

        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};
        s += board[row][col];
        if (trie.startsWith(s)) {
            if (trie.search(s)) {
                unique.insert(s);
            }
            char c = board[row][col];
            board[row][col] = '#';
            for (int i = 0; i < 4; i++) {
                helper(board, row + dy[i], col + dx[i], unique, s);
            }
            board[row][col] = c;
        }
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // 创建trie
        for (string w : words) {
            trie.insert(w);
        }

        // 遍历字母表，用trie判断prefix是否有效，如果无效不再继续DFS
        // 用trie判断word是否有效，有效就保存到最终结果中，继续DFS
        // 时间复杂度分析：1、遍历N个首字母O(N) 2、每个首字母DFS, O(N) 3、每个string调用trie, O(M)
        // 总的时间复杂度为O(N*N*2M)
        int m = board.size();
        int n = board[0].size();
        string s;
        vector<string> ans;
        unordered_set<string> unique;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                helper(board, i, j, unique, s);
            }
        }

        for (string w : unique) {
            ans.push_back(w);
        }

        return ans;
    }
private:
    Trie trie;
};
