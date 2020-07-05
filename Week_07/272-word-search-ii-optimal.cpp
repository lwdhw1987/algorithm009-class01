struct TrieNode {
    string word;
    //  不得不使用指针
    unordered_map<char, TrieNode*> next;
};

class Solution {
public:
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
};
