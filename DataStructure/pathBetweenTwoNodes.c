//Q: find a path from one node in BST to another.
//A: To get the lowest common ancestor of two nodes. LCA of tree.

node* GetLowestCommonAncestor(node* root, int value1, int value2){
	if (value1 > value2)
		swap(value1, value2); // make sure value1 < value2
	
	if (root->data > value1 && root->data > value2){
		GetLowestCommonAncestor(root->left, value1, value2);
	} else if (root->data < value1 && root->data < value2) {
		GetLowestCommonAncestor(root->right, value1, value2);
	} else if (root->data > value1 && root->data < value2){
		return root;
	}
	
	return NULL;
}
