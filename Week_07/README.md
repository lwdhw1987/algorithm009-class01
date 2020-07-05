# 用Trie数据结构解决word search问题时间复杂度分析
### 1. 实现Trie
```cpp
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
```

### 2.DFS遍历字母表，用trie判断单词是否有效，有效就保存到最终结果中，然后继续DFS
```cpp
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // 创建trie
        for (string w : words) {
            trie.insert(w);
        }

        // 遍历字母表，用trie判断prefix是否有效，如果无效不再继续DFS
        // 用trie判断word是否有效，有效就保存到最终结果中，继续DFS
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
```

### 3.时间复杂度分析
- 遍历N个首字母, 时间复杂度O(N)
- 每个首字母DFS, 时间复杂度O(N)
- 每个string调用trie判断是否有效, 时间复杂度O(M), M代表单词平均长度
- 总的时间复杂度为时间复杂度O(N\*N\*2M)
```cpp
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
```
### 4.改进方案，不必对单词表中每个字母都调用trie去判断string的有效性
- 首先改进Trie，将bool isWord改成string word，在insert方法中，如果遇到单词的尾节点，将单词保存到word中。
- 其次，在遍历字母表之前，根据单词表创建trie
- DFS过程中，用一个TrieNode指针跟踪当前字母对应的trie节点位置，直接判断指针指向的节点word是否有效。这样就
避免了每次从头访问trie节点。
- 遍历N个首字母, 时间复杂度O(N)
- 每个首字母DFS, 时间复杂度O(N)
- 每个构成string的字母判断对应trie中节点是否构成有效单词，时间复杂度O(1)
- 总时间复杂度O(N * N)
- trie insert函数
```cpp
TrieNode* insert(vector<string>& words) {
    TrieNode* root = new TrieNode();
    // 在trie中保存每个单词
    for (string word : words) {
        TrieNode* p = root;
        // 遍历每个字母，找到或插入新的节点，到最后一个字母，在节点中保存word
        for (char c : word) {
            if (p->next[c] == nullptr) {
                p->next[c] = new TrieNode();
            }
            p = p->next[c];
        }
        p->word = word;
    }
    return root;
}
```
- dfs helper
```cpp
// TrieNode* p用于追踪当前字母对应trie中的节点
void helper(vector<vector<char>>& board, int row, int col, vector<string>& ans, TrieNode* p) {
    int m = board.size();
    int n = board[0].size();
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] == '#') {
        return;
    }

    char c = board[row][col];
    if (p->next[c] == nullptr) {
        return;
    }

    p = p->next[c];
    if (p->word.size() > 0) {
        ans.push_back(p->word);
        // 防止重复解
        p->word = "";
    }
    board[row][col] = '#';
    for (int i = 0; i < 4; i++) {
        helper(board, row + dy[i], col + dx[i], ans, p);
    }
    board[row][col] = c;

}
```
- 主函数
```cpp
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    // 创建trie
    TrieNode* root = insert(words);

    // 遍历字母表，用trie判断prefix是否有效，如果无效不再继续DFS
    // 用trie判断word是否有效，有效就保存到最终结果中，继续DFS
    // 时间复杂度分析：1、遍历N个首字母O(N) 2、每个首字母DFS, O(N) 
    // 3、每个string判断word.size(), O(1)
    // 总的时间复杂度为O(N*N)
    int m = board.size();
    int n = board[0].size();
    vector<string> ans;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            helper(board, i, j, ans, root);
        }
    }

    return ans;
}
```


        
