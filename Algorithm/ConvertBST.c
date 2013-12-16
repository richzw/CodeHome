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
