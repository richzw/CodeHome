// Level order traversal in spiral form
// 1. print it by level

void printSpiral(Node* node) {
  int h = height(node);
  bool lhr = false;
  
  for (int i = 1; i <= h; ++i){
    printSpiralByOrder(node, i, lhr);
    lhr = !lhr;
  }
}

void printSpiralByOrder(Node* node, int level, bool lhr) {
  if (node == NULL)
    return;
  
  if (level == 1)
    print(node->data);
  else {
    if (lhr) {
      printSpiralByOrder(node->left, level-1, lhr);
      printSpiralByOrder(node->right, level-1, lhr);
    } else {
      printSpiralByOrder(node->right, level-1, lhr);
      printSpiralByOrder(node->left, level-1, lhr);
    }
  }
}

// 2. solve it through two stacks
void printSpiral(Node* node) {
  if (node == NULL)
    return;
    
  stack<int> stlr;
  stack<int> strl;
  
  stlr.push(node);
  
  while (!stlr.empty() || !strl.empty()) {
    while (!stlr.empty()) {
      Node* n = stlr.top();
      print(n->data);
      
      // Attention: different order
      if (n->right != NULL)
        strl.push(n->right);
      if (n->left != NULL)
        strl.push(n->left);
        
      stlr.pop();
    }
    
    while (!strl.empty()) {
      Node* n = strl.top();
      print(n->data);
      
      // Attention: different order
      if (n->left != NULL)
        stlr.push(n->left);
      if (n->right != NULL)
        stlr.push(n->right);
      
      strl.pop();
    }
  }
}

