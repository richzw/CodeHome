//http://courses.csail.mit.edu/6.006/fall09/lecture_notes/lecture03.pdf

struct node
{
	int time;
	int subTreeCnt;
	struct node *left, *right, *parent;
};

struct node* newNode(int time)
{
	struct node* temp = 
		(struct node*) malloc(sizeof(struct node));
	temp->time = time;
	temp->left = temp->right = NULL;
	return temp;
}

struct node* insert(struct node* root, int time, int k)
{
	if (root == NULL) return newNode(time);
	
	// check if this job conflicts with exsiting reservation
	if ((（time + k）> root->time) && ((time - k) < root->time))
		return root;
	
	if (time < root->time)
	{
		struct node* tmp = insert(root->left, time, k);
		root->left = tmp;
		tmp->parent = root;
	}
	else
	{
		struct node* tmp = insert(root->right, time, k);
		root->right = tmp;
		tmp->parent = root;
	}
	
	return root;	
}

struct node* minimum(struct node* cur)
{
	if (cur == NULL)
		return NULL;
	
	if (cur->left != NULL)
		cur = cur->left;
	
	return cur;
}

struct node* next_larger(struct node* current)
{
	struct node* parent = NULL;
	
	if (current == NULL)
		reutrn NULL;
	
	if (current->right != NULL)
		return mininum(current);
	else
		parent = current->parent;
	
	while (current != NULL && current == parent->right)
	{
		current = parent;
		parent = parent->parent;
	}
	
	return parent;
}
