// version 1
void get_min_max_length(TreeNode* root, int* min, int *max, int level){
	if (root == NULL)
		return;

	if (*min < level) *min = level;
	if (*max > level) *max = level;

	get_min_max_length(root->left, min, max, level-1);
	get_min_max_length(root->right, min, max, level+1);
}

void print_vertical_order(TreeNode* root, int ver_level, int level){
	if (root == NULL)
		return;

	if (level == ver_level)
		printf("%d", root->data);

	print_vertical_order(root->left, ver_level, level-1);
	print_vertical_order(root->right, ver_level, level+1);
}

void vertical_order(TreeNode* root){
	if (root == NULL)
		return;

	int min = 0, max = 0;
	get_min_max_length(root, &min, &max, 0);

	for (int idx = min; idx < max; ++idx){
		print_vertical_order(root, idx, 0);
	}
}

// version 2
// with hashmap
void traverse_tree(TreeNode* root, int level, map<int, vector<int> >& m /*key is the vlevel*/){
	if (root == NULL)
		return;

	m[level].push_back(root->data);

	traverse_tree(root->left, level-1, m);
	traverse_tree(root->right, level+1, m);
}

void vertical_order1(TreeNode* root){
	if (root == NULL)
		return;

	map<int, vector<int> > hmap;

	traverse_tree(root, 0, hmap);

	for (map<int, vector<int>>::iterator itor = hmap.begin(); itor != hmap.end(); ++itor){
		for (vector<int>::iterator it = itor->second.begin(); it != itor->second.end(); ++it){
			printf("%d ", *it);
		}
	}
}

// print tree vertical
void print_tree(TreeNode* root, int pos){
	if (root == NULL){
		for (int i = 0; i < pos; ++i)
			printf("\t");
		printf("*");
		return;
	}

	print_tree(root->right, pos+1);
	for (int i = 0; i < pos; ++i)
		printf("\t");
	printf("%d", root->data);
	print_tree(root->left, pos+1);
}
