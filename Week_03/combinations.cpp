/*
class Solution {
public:
    void helper(vector<int> aggregate, vector<vector<int>>& ans, int k, int start, int len) {
        if (k == 1) {
            // cout << "start = " << start << ", len = " << len << endl;
            for (int i = start; i < start + len; i++) {
                aggregate.push_back(i);
                ans.push_back(aggregate);
                aggregate.pop_back();
            }
            return;
        }
        
        if (k == len) {
            for (int i = start; i < start + len; i++) {
                aggregate.push_back(i);
            }
            ans.push_back(aggregate);
            return;
        }

        for (int i = 0; i <= len - k; i++) {
            aggregate.push_back(start + i);
            // cout << i << ": ";
            helper(aggregate, ans, k - 1, start + i + 1, len - i - 1);
            // cout << endl;
            aggregate.pop_back();
        }
        
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> aggregate;
        helper(aggregate, ans, k, 1, n);
        return ans;
    }
};
*/
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > rslt;
        vector<int> path(k, 0);
        combine(n, k, rslt, path);
        return rslt;
    }
private:
    void combine(int n, int k, vector<vector<int> > &rslt, vector<int> &path) {
        if (k == 0) {
            rslt.push_back(path);
            return;
        }
        for (int i = n; i >= 1; i--) {
            path[k - 1] = i;
            combine(i - 1, k - 1, rslt, path);
        }
    }
};
