/*
* Q1: Given a binary search tree, find the lowest common ancestor of two given nodes.
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
