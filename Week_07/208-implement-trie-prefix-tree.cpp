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
