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

// 2. by stack....

