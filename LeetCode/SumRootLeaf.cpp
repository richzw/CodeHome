/*
For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.   
*/


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct Qnode
{
  int sum_;
  TreeNode* p_;
  Qnode(int s, TreeNode *p):sum_(s),p_(p){}
  Qnode(){}
};
int sumNumbers(TreeNode *root) {
    if(root == NULL)
      return 0;
    queue<Qnode> myqueue;
    myqueue.push(Qnode(root->val, root));
    int res = 0;
    while(!myqueue.empty())
    {
        Qnode tmp = myqueue.front();
        myqueue.pop();
        if(tmp.p_->left == NULL && tmp.p_->right == NULL)
            res += tmp.sum_;
        else
        {
            if(tmp.p_->left != NULL)
                myqueue.push(Qnode(tmp.sum_*10 + tmp.p_->left->val, tmp.p_->left));
            if(tmp.p_->right != NULL)
                myqueue.push(Qnode(tmp.sum_*10 + tmp.p_->right->val, tmp.p_->right));
        }
    }
    return res;
}
