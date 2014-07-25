/*
* Q1: Given a binary search tree, find the lowest common ancestor of two given nodes.
*/
typedef struct elem{
  	elem*	left;
	elem*	right;
	int	data;
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

/*
* Q2: Given a binary tree, find the lowest common ancestor of two given nodes in the tree.
*/
int LCA_number(elem* root, int a, int b){
	if (!root)
		return 0;
	if (root->data == a || root->data == b){
		return 1 + LCA_number(root->left, a, b) + LCA_number(root->right, a, b);
	}else{
		return LCA_number(root->left, a, b) + LCA_number(root->right, a, b);
	}
}

//TOP_DOWN approach
int LCA_BT(elem* root, int a, int b){
	if (!root)
		return -1;
	
	if (root->data == a || root->data == b)
		return root->data;

	int has_elem_left = LCA_number(root->left, a, b);
	int has_elem_right = LCA_number(root->right, a, b);

	if (has_elem_left == 1 && has_elem_right == 1)
		return root->data;
	else if (has_elem_left == 2)
		return LCA_BT(root->left, a, b);
	else if (has_elem_right == 2)
		return LCA_BT(root->right, a, b);
}

//better solution
Node *LCA(Node *root, Node *p, Node *q) {
	if (!root) return NULL;
	if (root == p || root == q) return root;

	Node *L = LCA(root->left, p, q);
	Node *R = LCA(root->right, p, q);
	if (L && R) 
	  	return root;  // if p and q are on both sides
	return L ? L : R;  // either one of p,q is on one side OR p,q is not in L&R subtrees
}

// the robust version
TreeNode *findLCAUtil(TreeNode* root, int n1, int n2, bool &v1, bool &v2)
{
    if (root == NULL) return NULL;
 
    // If either n1 or n2 matches with root's key, report the presence
    // by setting v1 or v2 as true and return root (Note that if a key
    // is ancestor of other, then the ancestor key becomes LCA)
    if (root->data == n1)
    {
        v1 = true;
        return root;
    }
    if (root->data == n2)
    {
        v2 = true;
        return root;
    }
 
    // Look for keys in left and right subtrees
    TreeNode *left_lca  = findLCAUtil(root->left, n1, n2, v1, v2);
    TreeNode *right_lca = findLCAUtil(root->right, n1, n2, v1, v2);
 
    // If both of the above calls return Non-NULL, then one key
    // is present in once subtree and other is present in other,
    // So this node is the LCA
    if (left_lca && right_lca)  return root;
 
    // Otherwise check if left subtree or right subtree is LCA
    return (left_lca != NULL)? left_lca: right_lca;
}
 
// Returns true if key k is present in tree rooted with root
bool find(TreeNode *root, int k)
{
    // Base Case
    if (root == NULL)
        return false;
 
	if (root->data == k || find(root->left, k) ||  find(root->right, k))
        return true;

    return false;
}
 
// This function returns LCA of n1 and n2 only if both n1 and n2 are present
// in tree, otherwise returns NULL;
TreeNode *findLCA(TreeNode *root, int n1, int n2)
{
    // Initialize n1 and n2 as not visited
    bool v1 = false, v2 = false;
 
    // Find lca of n1 and n2 using the technique discussed above
    TreeNode *lca = findLCAUtil(root, n1, n2, v1, v2);
 
    // Return LCA only if both n1 and n2 are present in tree
    if (v1 && v2 || v1 && find(lca, n2) || v2 && find(lca, n1))
        return lca;
 
    return NULL;
}


/*
* Q3: Given a binary tree, find the lowest common ancestor of two given nodes in the tree. 
*     Each node contains a parent pointer which links to its parent.
*/

typedef struct treenode{
	treenode* father;
	treenode* left;
	treenode* right;
	int		  data;
}treenode;

treenode* LCA_tree(treenode* root, int a, int b){
	vector<treenode*> treenode_queue;
	int tree_index = 0;
	treenode* ptreenode_a = NULL;
	treenode* ptreenode_b = NULL;

	//Breadth-First Search -- level-order search
	treenode_queue.push_back(root);
	while((treenode_queue.size() - tree_index) > 0){
		treenode* pnode = treenode_queue[tree_index];
		if (pnode->left != NULL){
			treenode_queue.push_back(pnode->left);
			if (pnode->left->data == a)
				ptreenode_a = pnode->left;
		}
		if (pnode->right != NULL){
			treenode_queue.push_back(pnode->right);
			if (pnode->right->data == b)
				ptreenode_b = pnode->right;
		}
		++tree_index;
	}
	
	//check whether the parent node is visited, 
	//if so, that is LCA. otherwise, go to parent node.
	set<treenode*> parent_nodes;
	pair<set<treenode*>::iterator,bool> ret;
	while(true){
		if (ptreenode_a){
			ret = parent_nodes.insert(ptreenode_a);
			if (ret.second == false)
				return *(ret.first);
			ptreenode_a = ptreenode_a->father;
		}
		if (ptreenode_b){
			ret = parent_nodes.insert(ptreenode_b);
			if (ret.second == false)
				return *(ret.first);
			ptreenode_b = ptreenode_b->father;
		}
	}
}

//better solution for Q3
int tree_depth(Node *p) {
	if (p == NULL)
		return 0;
	else
		return 1+tree_depth(p->father);
}
 
Node *LCA(Node *p, Node *q) {
  	int h1 = tree_depth(p);
  	int h2 = tree_depth(q);
  	// swap both nodes in case p is deeper than q.
  	if (h1 > h2) {
    		swap(h1, h2);
    		swap(p, q);
  	}
  	// invariant: h1 <= h2.
  	int dh = h2 - h1;
  	for (int h = 0; h < dh; h++)
    		q = q->parent;
  	while (p && q) {
    		if (p == q) return p;
    		p = p->parent;
    		q = q->parent;
  	}
  	return NULL;  // p and q are not in the same tree
}
