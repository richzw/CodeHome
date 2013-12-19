/*
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST),
where largest means subtree with largest number of nodes in it.
*/
int findLargestSubTreeHelper(bst_node* root, int& min, int& max, int& maxNodeNum, bst_node*& largestTree){
	if (!root)
		return 0;

	int isBst = true;
	int leftnodes = findLargestSubTreeHelper(root->left, min, max, maxNodeNum, largestTree);
	int curmin = (leftnodes == 0) ? root->data:min;
	if ((leftnodes == -1) || ((leftnodes != 0) && (root->data <= max)))
		isBst = false;

	int rightnodes = findLargestSubTreeHelper(root->right, min, max, maxNodeNum, largestTree);
	int curmax = (rightnodes == 0)? root->data:max;
	if ((rightnodes == -1) || ((rightnodes != 0) && (root->data >= min)))
		isBst = false;

	if (isBst){
		min = curmin;
		max = curmax;
		int curnodes = leftnodes + rightnodes + 1;
		if (curnodes > maxNodeNum){
			maxNodeNum = curnodes;
			largestTree = root;
		}

		return curnodes;
	}else{
		return -1;
	}
}

bst_node* findLargestSubTree(bst_node* root){
	bst_node* largest_tree = NULL;
	int min, max;
	int max_nodes = 0;

	findLargestSubTreeHelper(root, min, max, max_nodes, largest_tree);

	return largest_tree;
}
