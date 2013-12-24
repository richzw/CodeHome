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

/*
Convert a BST to a sorted circular doubly-linked list in-place. 
Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.
http://cslibrary.stanford.edu/109/TreeListRecursion.html
*/
/*
 helper function -- given two list nodes, join them
 together so the second immediately follow the first.
 Sets the .next of the first and the .previous of the second.
*/
static void join(Node a, Node b) {
    a->large = b;
    b->small = a;
}


/*
 helper function -- given two circular doubly linked
 lists, append them and return the new list.
*/
static Node append(Node a, Node b) {
    Node aLast, bLast;
    
    if (a==NULL) return(b);
    if (b==NULL) return(a);
    
    aLast = a->small;
    bLast = b->small;
    
    join(aLast, b);
    join(bLast, a);
    
    return(a);
}


/*
 --Recursion--
 Given an ordered binary tree, recursively change it into
 a circular doubly linked list which is returned.
*/
static Node treeToList(Node root) {
    Node aList, bList;
    
    if (root==NULL) return(NULL);

    /* recursively solve subtrees -- leap of faith! */
    aList = treeToList(root->small);
    bList = treeToList(root->large);
    
    /* Make a length-1 list ouf of the root */
    root->small = root;
    root->large = root;

    /* Append everything together in sorted order */
    aList = append(aList, root);
    aList = append(aList, bList);
    
    return(aList);
}
