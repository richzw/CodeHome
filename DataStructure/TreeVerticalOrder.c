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

