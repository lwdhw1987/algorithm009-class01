class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        stack<Node*> nodes;
        if (root) nodes.push(root);
        while (!nodes.empty()) {
            Node* p = nodes.top();
            nodes.pop();
            ans.push_back(p->val);
            vector<Node*> children = p->children;
            for (auto it = children.rbegin(); it != children.rend(); it++) {
                nodes.push(*it);
            }
        }
        return ans;
    }
};
