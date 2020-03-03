/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 class Solution {
    public:
        int maxDepth(TreeNode* root) {
            if (root==NULL)
                return 0;
            root->val=1;
            int res=0;
            queue<TreeNode*>q;
            q.push(root);
            while (!q.empty()){
                TreeNode *temp=q.front();
                q.pop();
                res=max(res,temp->val);
                if (temp->left!=NULL){
                    temp->left->val=temp->val+1;
                    q.push(temp->left);
                }
                if (temp->right!=NULL){
                    temp->right->val=temp->val+1;
                    q.push(temp->right);
                }
            }
            return res;
        }
    };