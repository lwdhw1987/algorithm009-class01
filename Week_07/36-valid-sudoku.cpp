class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();
        int row[9][10] =  {};
        int col[9][10] =  {};
        int grid[9][10] = {};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x = board[i][j] - '0';
                if (x < 0 || x > 9) continue;
                if (row[i][x] || col[j][x] || grid[(i/3)*3+j/3][x])
                {
                    return false;
                }
                row[i][x]++;
                col[j][x]++;
                grid[(i/3)*3+j/3][x]++;
            }
        }

        return true;
    }
};
