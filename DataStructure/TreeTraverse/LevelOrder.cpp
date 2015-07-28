// level order of binary tree
// 1. print it by level
int height(Node* node) {
  if (node == NULL)
    return 0;
  else {
    int lh = height(node->left);
    int rh = height(node->right);
    
    if (lh > rh)
      return lh + 1;
    else
      return rh + 1;
  }
}

void printLevelOrder(Node* node) {
  int h = height(node);
  
  for (int i = 1; i <= h; ++i)
    printGivenLevel(node, i);
}

void printGivenLevel(Node* node, int l) {
  if (node == NULL)
    return;
  if (l == 1)
    print(node->data);
  else {
    printGivenLevel(node->left, l - 1);
    printGivenLevel(node->right, l - 1);
  }
}

// level order by queue
/*
printLevelorder(tree)
1) Create an empty queue q
2) temp_node = root //start from root
3) Loop while temp_node is not NULL
    a) print temp_node->data.
    b) Enqueue temp_node’s children (first left then right children) to q
    c) Dequeue a node from q and assign it’s value to temp_node
    */
