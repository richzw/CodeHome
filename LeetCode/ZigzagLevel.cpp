/*
Given a binary tree, return the zigzag level order traversal of its nodes' values.
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
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
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        TreeNode * q1[10000];
        bool q2[10000];
        int begin=0;
        int end=0;
        
        if(root == NULL)
        {
            vector<vector<int> > v;
            return v;
        }
        else
        {
            vector<vector<int> > v;
            q1[end] = root;
            q2[end++] = true;
            
            bool level = true;
            bool cur = true;
            
            vector<int> * tmp = new vector<int>();
            while(begin!=end)
            {
                TreeNode * p = q1[begin];
                cur = q2[begin++];
                
                if(cur != level)
                {
                    if(!level)
                    {
                        for(int k=0;k<tmp->size()/2;k++)
                        {
                            int t = tmp->at(k);
                            tmp->at(k) = tmp->at(tmp->size()-1-k);
                            tmp->at(tmp->size()-1-k) = t;
                        }
                        v.push_back(*tmp);
                    }
                    else
                    {
                        v.push_back(*tmp);
                    }
                    delete tmp;
                    tmp = new vector<int>();
                    level = !level;
                    
                }
                if(cur == level)
                {
                    if(p->left != NULL)
                    {
                        q1[end] = p->left;
                        q2[end++] = !cur;
                    }
                    if(p->right != NULL)
                    {
                        q1[end] = p->right;
                        q2[end++] = !cur;
                    }
                    tmp->push_back(p->val);
                }
                
            }
            if(!level)
            {
                for(int k=0;k<tmp->size()/2;k++)
                {
                    int t = tmp->at(k);
                    tmp->at(k) = tmp->at(tmp->size()-1-k);
                    tmp->at(tmp->size()-1-k) = t;
                }
                v.push_back(*tmp);
            }
            else
            {
                
                v.push_back(*tmp);
            }
            return v;
        }
    }
};
