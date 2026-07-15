/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string ans = "";
    string path = "";

    void dfs(TreeNode* root) {
        if (root == NULL)
            return;

        path.push_back(root->val + 'a');

        if (root->left == NULL && root->right == NULL) {
            string curr = path;
            reverse(curr.begin(), curr.end());

            if (ans == "" || curr < ans)
                ans = curr;
        }

        dfs(root->left);
        dfs(root->right);

        path.pop_back();
    }

    string smallestFromLeaf(TreeNode* root) {
        dfs(root);
        return ans;
    }
};