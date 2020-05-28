class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        int size = 0;
        queue<Node*> fifo;
        if (root) {
            fifo.push(root);
            size++;
        }

        vector<vector<int>> ans;
        while (!fifo.empty()) {
            int size_new = 0;
            vector<int> vals;
            while (size--) {
                Node* p = fifo.front();
                vals.push_back(p->val);
                fifo.pop();
                for (Node* q : p->children) {
                    fifo.push(q);
                    size_new++;
                }
            }
            ans.push_back(vals);
            size = size_new;
        }

        return ans;
    }
};
