/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

top-down solution: run time complexity is O(NlgN), easy to implementation
bottom-up solution: run time complexity is O(N), difficult to verify
*/
typedef struct list_node{
	int data;
	list_node* next;
}list_node;

bst_node* sortedlistToBSTHelper(list_node* sortList, int begin, int end){
	if (begin > end)
		return NULL;

	int mid = begin + (end-begin)/2;
	bst_node* leftchild = sortedlistToBSTHelper(sortList, begin, mid-1);

	bst_node* parent = new bst_node();
	parent->left = leftchild;
	parent->data = sortList->data;
	sortList = sortList->next;
	parent->right = sortedlistToBSTHelper(sortList, mid+1, end);

	return parent;
}

bst_node* sortedlistToBST(list_node* sortList, int len){

	return sortedlistToBSTHelper(sortList, 0, len-1);
}
