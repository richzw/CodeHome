/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/
typedef struct bst_node{
	int data;
	bst_node* left;
	bst_node* right;
}bst_node;

bst_node* convertoBSTHelper(int arr[], int left, int right){
	if (left > right)
		return NULL;

	int mid = (left + right)>>2;

	bst_node* node = new bst_node();
	node->data = arr[mid];
	node->left = convertoBSTHelper(arr, left, mid-1);
	node->right = convertoBSTHelper(arr, mid+1, right);

	return node;
}

bst_node* sortedArrayConvertoBST(int arr[], int len){
	return convertoBSTHelper(arr, 0, len-1);
}

/*Write a function isBST(BinaryTree *node) to verify if a given binary tree is a Binary Search Tree (BST) or not.*/
bool isBstLessThan(bst_node* tree, int val){
	if (!tree)
		return true;
	return (tree->data < val &&
		isBstLessThan(tree->left, val)&&
		isBstLessThan(tree->right, val));
}

bool isBstGreaterThan(bst_node* tree, int val){
	if (!tree)
		return true;
	return (tree->data > val &&
		isBstGreaterThan(tree->left, val) &&
		isBstGreaterThan(tree->right, val));
}

bool isBstBruteForce(bst_node* tree){
	if (!tree)
		return true;

	return (isBstLessThan(tree->left, tree->data)&&
		isBstGreaterThan(tree->right, tree->data)&&
		isBstBruteForce(tree->left)&&
		isBstBruteForce(tree->right));
}

// more better solution
bool isBstHelper(bst_node* tree, int min, int max){
	if (!tree)
		return true;

	if (tree->data > min && tree->data < max)
		return (isBstHelper(tree->left, min, tree->data)&&
		isBstHelper(tree->right, tree->data, max));
	else
		return false;
}

bool isBst(bst_node* tree){
	if (!tree)
		return true;

	return isBstHelper(tree, INT_MIN, INT_MAX);
}
