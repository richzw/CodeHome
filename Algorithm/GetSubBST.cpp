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

/*
Given a binary tree, find the largest Binary Search Tree (BST), where largest means BST with largest number of nodes in it.
The largest BST may or may not include all of its descendants.
*/
int findLargestBSTHelper(bst_node* root, int min, int max, int& maxNodeNum, 
								bst_node*& largestTree, bst_node*& child){
	if (!root)
		return 0;

	if (min < root->data && root->data < max){
		int leftnodes = findLargestBSTHelper(root->left, min, root->data, maxNodeNum, largestTree, child);
		bst_node* left_child = (leftnodes == 0)? NULL:child;
		
		int rightnodes = findLargestBSTHelper(root->right, root->data, max, maxNodeNum, largestTree, child);
		bst_node* right_child = (rightnodes == 0)? NULL:child;

		bst_node* parent = new bst_node();
		parent->left = left_child;
		parent->right = right_child;
		parent->data = root->data;
		child = parent;

		int curnodes = leftnodes + rightnodes +1;
		if (curnodes > maxNodeNum){
			maxNodeNum = curnodes;
			largestTree = parent;
		}

		return curnodes;
	}else{
		//treat this node as an entirely new tree and 
		// check if a larger BST exist in this tree
		findLargestBSTHelper(root, INT_MIN, INT_MAX, maxNodeNum, largestTree, child);
		return 0;
	}
}

bst_node* findLargestBST(bst_node* root){
	int min = INT_MIN;
	int max = INT_MAX;
	int max_node = 0;
	bst_node* largestTree = NULL;
	bst_node* child;

	findLargestBSTHelper(root, min, max, max_node, largestTree, child);
	return largestTree;
}
