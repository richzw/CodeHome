
/*
Q: Vertex cover for tree

A vertex cover of an undirected graph is a subset of its vertices such that for every edge (u, v) of the graph,
either ‘u’ or ‘v’ is in vertex cover.

The idea is to consider following two possibilities for root and recursively for all nodes down the root.

1) Root is part of vertex cover: In this case root covers all children edges. We recursively calculate size of vertex covers 
for left and right subtrees and add 1 to the result (for root).

2) Root is not part of vertex cover: In this case, both children of root must be included in vertex cover to 
cover all root to children edges. We recursively calculate size of vertex covers of all grandchildren and
number of children to the result (for two children of root).

*/

int vertexCoverForBinaryTree(struct Node* root)
{
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 0;
  
  // root is part of vertex cover
  int root_cnt = 1 + vertexCoverBinaryTree(root->left) + vertexCoverBinaryTree(root->right);
  
  // root is not part of vertex cover
  int noroot_cnt = 0;
  if (root->left != NULL)
    //noroot_cnt = 1 + vertexCoverBinaryTree(root->left);
    noroot_cnt = 1 + vertexCoverBinaryTree(root->left->left) + vertexCoverBinaryTree(root->left->right); // Fixme
  if (root->right != NULL)
    //noroot_cnt = 1 + vertexCoverBinaryTree(root->right);
    noroot_cnt = 1 + vertexCoverBinaryTree(root->right->left) + vertexCoverBinaryTree(root->right->right); // Fixme
  
  return std:min(noroot_cnt, root_cnt);
}

// Issue: time complexity of the above naive recursive approach is exponential.

// Improvement: Dynamic Programming
// re-computations of same subproblems can be avoided by storing the solutions to subproblems and 
// solving problems in bottom up manner.

typedef struct node {
  node* left;
  node* right;
  int val;
  int vc_cnt;  // store the vertex cover count 
};

int vertexCoverDP(struct node* root)
{
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 0;
    
  //If vertex cover for this node is already evaluated, just return it.
  if (root->vc_cnt > 0)
    return root->vc_cnt;
  
  int root_cnt = 1 + vertexCoverDP(root->left) + vertexCoverDP(root->right);
  
  int noroot_cnt = 0;
  if (root->left)
    noroot_cnt += 1 + vertexCoverDP(root->left->left) + vertexCoverDP(root->left->right);
  if (root->right)
    noroot_cnt += 1 + vertexCoverDP(root->right->left) + vertexCoverDP(root->right->right);
  
  root->vc_cnt = std::min(root_cnt, noroot_cnt);
  return root->vc_cnt;
}
