class Solution {
public:
    void inorder(vector<int>& ans, TreeNode* root) {
        if (root == NULL) return;
        // 先遍历左子树
        inorder(ans, root->left);
        // 插入当前节点
        ans.push_back(root->val);
        // 遍历右子树
        inorder(ans, root->right);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inorder(ans, root);
        return ans;
    }
};
