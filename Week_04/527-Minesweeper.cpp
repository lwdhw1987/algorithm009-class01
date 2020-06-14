// BFS
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size();
        int n = board[0].size();
        vector<bool> visited(m * n, false);
        vector<vector<char>> ans = board;
        vector<pair<int, int>> dir = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                                      {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

        queue<pair<int, int>> fifo;
        fifo.push({click[0], click[1]});
        int k = click[0] * n + click[1];
        while (!fifo.empty()) {
            pair<int, int> coordinate = fifo.front();
            fifo.pop();
            int row = coordinate.first;
            int col = coordinate.second;

            if (ans[row][col] == 'M') {
                ans[row][col] = 'X';
                return ans;
            }

            if (ans[row][col] != 'E') {
                continue;
            }

            int count = 0;
            vector<pair<int, int>> adj;
            for (auto d : dir) {
                int row_new = row + d.first;
                int col_new = col + d.second;
                if (row_new < 0 || row_new >= m || col_new < 0 || col_new >= n) {
                    continue;
                }
                if (ans[row_new][col_new] == 'M') {
                    count++;
                    continue;
                }
                adj.push_back({row_new, col_new});
            }
            if (count > 0) {
                ans[row][col] = count + '0';
            }
            else {
                ans[row][col] = 'B';
                for (auto item : adj) {
                    fifo.push(item);
                }
            }
        }

        return ans;
    }
};


class Solution {
public:
    void helper(vector<vector<char>>& board, int row, int col, int dir[][2]) {
        int m = board.size();
        int n = board[0].size();
        // 利用格子状态的变化避免重复遍历
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] != 'E') {
            return;
        }
        
        int count = 0;
        for (int i = 0; i < 8; i++) {
            int row_new = row + dir[i][0];
            int col_new = col + dir[i][1];
            if (row_new >= 0 && row_new < m && col_new >= 0 && col_new < n 
                && board[row_new][col_new] == 'M') {
                count++;
            }
        }

        if (count == 0) {
            board[row][col] = 'B';
            for (int i = 0; i < 8; i++) {
                int row_new = row + dir[i][0];
                int col_new = col + dir[i][1];
                helper(board, row_new, col_new, dir);
            }
        }
        else {
            board[row][col] = count + '0';
        }
    }

    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int dir[8][2] =  {{1, 1}, {-1, -1}, {0, 1}, {0, -1}, 
                          {1, 0}, {-1, 0}, {-1, 1}, {1, -1}};
        vector<vector<char>> ans = board;
        int row = click[0];
        int col = click[1];
        if (ans[row][col] == 'M') {
            ans[row][col] = 'X';
            return ans;
        }
        helper(ans, row, col, dir);
        return ans;
    }
};
