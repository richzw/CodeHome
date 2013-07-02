 /*
  * Read BST from file: save BST into file via pre-order traversal,
  * cause A node's parent is always output before itself.
  */
 void readBSTHelper(int minVal, int maxVal, int val, node*& root, ifstream& fin){
     if (minVal < val && val < maxVal){
         node *pnode = new node();
         pnode->data = val;
         int new_val;
         fin >> new_val;
         if (new_val){
             readBSTHelper(minVal, val, new_val, pnode->left, fin);
             readBSTHelper(val, maxVal, new_val, pnode->right, fin);
         }
     }
 }

 void readBST(struct node*& root, ifstream &fin){
     int val;
     fin >> val;
     readBSTHelper(INT_MIN, INT_MAX, val, root, fin);
 }


// same idea to solve the quetion: how to check tree is BST?
/*
 * Return true if the binary tree is BST (efficient version)
 */
bool isBST_e(struct node* node){
    return isBSTUtil(node, INT_MIN, INT_MAX);
}

bool isBSTUtil(struct node* node, int min, int max){
    if (NULL == node)
        return true;

    // false if this node violates the min/max constraint
    if (node->data < min || node->data > max)
        return false;

    // otherwise check the subtree recrusively
    return isBSTUtil(node->left, min, node->data) &&
            isBSTUtil(node->right, node->data+1, max);
}
