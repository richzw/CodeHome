/*Given preorder and inorder traversal of a tree, construct the binary tree.*/
int indexOfInorder(int arr[], int len, int key){
	if (len <= 0)
		return -1;

	for (int i = 0; i < len; ++i){
		if (arr[i] == key)
			return i;
	}

	return -1;
}

tree_node* buildTreePreorderInorder(int in[], int pre[], int len, int offset){
	if (len <= 0)
		return NULL;

	tree_node* root = new tree_node();
	int index = indexOfInorder(in, len, pre[0]);
	if (index == -1)
		return NULL;

	root->data = pre[0];
	root->left = buildTreePreorderInorder(in, pre+1, index, offset);
	root->right = buildTreePreorderInorder(in+index+1, pre+index+1, len-index-1, offset+index+1);

	return root;
}
