class Solution {
public:
    int Find(int p) {
        while (p != id[p]) {
            id[p] = id[id[p]]; // 路径减半
            p = id[p];
        }
        return p;
    }

    bool connected(int p, int q) {
        return Find(p) == Find(q);
    }

    void Union(int p, int q) {
        int rootP = Find(p);
        int rootQ = Find(q);
        if (rootP == rootQ) return;
        if (size[rootP] < size[rootQ]) {
            id[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        else {
            id[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }

    void solve(vector<vector<char>>& board) {
        if (board.empty()) {
            return;
        }

        int n = board.size();
        int m = board[0].size();
        for (int i = 0; i <= m * n; i++) {
            id.push_back(i);
            size.push_back(1);
        }

        // 遍历board, 将'O'连接在一起, 并且边界的'O'与m * n连接
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    Union(i * m + j, m * n);
                }

                if (board[i][j] == 'O') {
                    if (i + 1 < n && board[i+1][j] == 'O') {
                        Union(i * m + j, (i + 1) * m + j);
                    } 
                    if (j + 1 < m && board[i][j+1] == 'O') {
                        Union(i * m + j, i * m + j + 1);
                    }
                }
            }
        }

        // 遍历边界内，如果是'O'且不与m * n相连，将其设置成'X'
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < m - 1; j++) {
                if (board[i][j] == 'O' && !connected(i * m + j, m * n)) {
                    board[i][j] = 'X';
                }
            }
        }

    }
private:
    vector<int> id;
    vector<int> size;
};
