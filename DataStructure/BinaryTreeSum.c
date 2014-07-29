//Q1. Given a Binary Tree, find the maximum sum path from a leaf to root. 

void printPath(TreeNode* root, TreeNode* target_leaf){
  if (root == NULL)
    return NULL;
    
  if (root == target_leaf || printPath(root->left, target_leaf) || printPath(root->right, target_leaf)){
    printf ("%d", root->data);
    return true;
  }
  
  return false;
}

void getTargetLeaf(TreeNode* root, int* sum_ref, int cur_sum, TreeNode** target_leaf_ref){
  if (root == NULL)
    return;
    
  cur_sum = cur_sum + root->data;
  if (root->left == NULL && root->right == NULL){
    if (cur_sum > *sum_ref){
      *sum_ref = cur_sum;
      *target_leaf_ref = root;
    }
  }
  
  getTargetLeaf(root->left, sum_ref, cur_sum, target_leaf_ref);
  getTargetLeaf(root->right, sum_ref, cur_sum, target_leaf_ref);
}

int maxSumPathFromRoot(TreeNode* root){
  if (root == NULL)
    return 0;
    
  TreeNode* target_leaf;
  int max_sum = INT_MIN;
  
  getTargetLeaf(root, &max_sum, 0, &target_leaf);
  
  printPath(root, target_leaf);
  
  return max_sum;
}
//Q2: Given a binary tree in which each node element contains a number. 
//Find the maximum possible sum from one leaf node to another.

/*
We can find the maximum sum using single traversal of binary tree. The idea is to maintain two values in recursive calls
1) Maximum root to leaf path sum for the subtree rooted under current node.
2) The maximum path sum between leaves (desired output).
*/
