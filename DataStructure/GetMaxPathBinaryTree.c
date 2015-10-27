
//Given a binary tree, find the maximum path sum. The path may start and end at any node in the tree.

/*
 For each node there can be four ways that the max path goes through the node:
1. Node only
2. Max path through Left Child + Node
3. Max path through Right Child + Node
4. Max path through Left Child + Node + Max path through Right Child
*/

int findMaxUntil(Node* root, int& maxVal)
{
  if (root == NULL)
    return 0;
  
  int l = findMaxUntil(root->left, maxVal);
  int r = findMaxUntil(root->right, maxVal);
  
  int maxCur = max(max(l, r) + root->data, root->data);
  
  int maxTotal = max(maxCur, l+r+root->data);
  
  maxVal = max(maxTotal, maxVal);
  
  return maxCur;
}

int findMaxPath(Node* root)
{
  int ret = INT_MIN;
  
  findMaxUtil(root, ret);
  
  return ret;
}
