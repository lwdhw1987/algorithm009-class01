class Solution {
public:
    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int& i, int left, int right) {
        if (left > right) return nullptr;
        int j = hash[preorder[i]];
        TreeNode* root = new TreeNode(preorder[i++]);

        root->left = helper(preorder, inorder, i, left, j - 1);
        root->right = helper(preorder, inorder, i, j + 1, right);
        
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        for (int i = 0; i < inorder.size(); i++) {
            hash[inorder[i]] = i;
        }

        return helper(preorder, inorder, i, 0, inorder.size() - 1);
    }

private:
    unordered_map<int, int> hash; 
};
