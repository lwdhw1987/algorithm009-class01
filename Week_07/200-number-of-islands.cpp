class Solution {
public:
    int Find(int p) {
        while (id[p] != p) {
            id[p] = id[id[p]]; // 路径减半
            p = id[p];
        }
        return p;
    }

    void Union(int p, int q) {
        int rootP = Find(p);
        int rootQ = Find(q);
        if (rootP == rootQ) return;
        id[rootP] = rootQ;
        count--;
        return;
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int n = grid.size();
        int m = grid[0].size();
        count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // cout << grid[i][j] << endl;
                if (grid[i][j] == '1') {
                    count++;
                }
                id.push_back(i * m + j);
            }
        }

        // 遍历岛屿如果当前为'1'将其与周围的'1'连接，避免重复访问。
        // 最后统计并查集的集合个数
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    if (i + 1 < n && grid[i+1][j] == '1') {
                        Union(i * m + j, (i + 1) * m + j);
                    }
                    if (j + 1 < m && grid[i][j+1] == '1') {
                        Union(i * m + j, i * m + j + 1);
                    }
                }
            }
        }
        
        return count;
    }
private:
    vector<int> id;
    int count;
};
