/*
* Q: Given a binary search tree, find the lowest common ancestor of two given nodes.
*/

typedef struct elem{
  elem*	left;
	elem*	right;
	int		data;
}elem;

int LCA_BST(elem* root, int a, int b){
	if (!root)
		return NULL;

	if ((root->data == a || root->data == b) || // a node to be descendant of itself
		(root->data > a && root->data < b) ||
		(root->data < a && root->data > b))
		return root->data;
	else if (root->data < a && root->data < b)
		return LCA_BST(root->left, a, b);
	else
		return LCA_BST(root->right, a, b);
}

