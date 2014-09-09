//find paths which sum to a given value in a binary tree
typedef struct TreeNode{
	TreeNode* left;
	TreeNode* right;
	int data;
	vector<int> sums;
}TreeNode;

void printPath(int path[], int start, int end){
	for (int i = start; i < end; ++i){
		printf("%d ->", path[i]);
	}
	printf("/n");
}

int treeDepth(TreeNode* root){
	if (root == NULL)
		return 0;
	else
		return 1+std::max(treeDepth(root->left), treeDepth(root->right));
}

void findSum(TreeNode* root, int sum, int path[], int level){
	if (root == NULL)
		return;

	path[level] = root->data;

	int tmp = 0;
	for (int id = level; id >= 0; --id){
		tmp += path[id];
		if (tmp == sum)
			printPath(path, id, level);
	}

	findSum(root->left, sum, path, level+1);
	findSum(root->right, sum, path, level+1);

	path[level] = 0;
}
