//Q:find K-th smallest element in BST.

typedef struct node {
	int val;
	node* left;
	node* right;
}node;

//method 1: Inorder traversal, O(n) where n is the total nodes in tree.
// part 1: recursive version
void findKth(node* root, int& k){
	if (!root || k < 0)
		return;
	
	findKth(p->left, k);
	--k;
	if (k == 0){
		printf("%d", p->val);
		return;
	}
	
	findKth(p->right, k);
}

// part 2: non-recursive version
node* kth_smallest_element_inorder(node* root, int k){
	stack<node*> st;
	node* pCrawl = root;

	// move to the left minimum
	while (pCrawl){
		st.push(pCrawl);
		pCrawl = pCrawl->left;
	}

	// pop off stack and process each node
	while (pCrawl = st.top()){
		st.pop();
		if (!--k){ 
			// output the k smallest elements
			cout << pCrawl->val << " ";
			break;
		}

		// there is right subtree
		if (pCrawl->right){
			pCrawl = pCrawl->right;
			while (pCrawl){
				st.push(pCrawl);
				pCrawl = pCrawl->left;
			}
		}
	}

	return pCrawl;
}

// method 2: maintain rank of each node, and keep track of the elements
//          a subtree of any node while building the tree
typedef struct node_t{
	int val
	node_t* left;
	node_t* right;
	int count;
}node_t;

int kth_smallest_element_by_rank(node_t* root, int k){
	int ret = -1;

	if (root){
		// a crawling pointer
		node_t* ptraverse = root;

		while (ptraverse){
			if (ptraverse->count + 1 == k){
				ret = ptraverse->val;
				break;
			} else if (k > ptraverse->count){
				k = k - ptraverse->count - 1;
				ptraverse = ptraverse->right;
			} else {
				ptraverse = ptraverse->left;
			}

		}
	}
	return ret;
}

// Ref:http://stackoverflow.com/questions/2329171/find-kth-smallest-element-in-a-binary-search-tree-in-optimum-way
// stackoverflow.com/a/23069077/278326
