class Solution {
public:
    TreeNode* helper(TreeNode* root, int p, int q) {
        if (!root) return nullptr;
        if (root->val == p || root->val == q) return root;

        TreeNode* left = helper(root->left, p, q);
        TreeNode* right = helper(root->right, p, q);
        if (!left) return right;
        if (!right) return left;
        return root;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return helper(root, p->val, q->val);
    }
};
