class Solution {
public:
    int Find(int p) {
        while (p != id[p]) {
            // 路径减半
            // https://algs4.cs.princeton.edu/15uf/QuickUnionPathHalvingUF.java.html
            id[p] = id[id[p]];
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
    }

    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        count = n;
        for (int i = 0; i < n; i++) {
            id.push_back(i);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (M[i][j] == 1) {
                    Union(i, j);
                }
            }
        }

        return count;
    }
private:
    vector<int> id;
    int count;

};
