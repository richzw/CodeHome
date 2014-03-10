/*
在二叉搜索树中找最小的大于某个key值的节点
*/
struct TreeNode{
	int data;
	TreeNode* left;
	TreeNode* right;
};
TreeNode* findCeiling(TreeNode* root, int key){
	TreeNode* ceiling = NULL;
	TreeNode* current = root;

	while (current){
		if (current->data <= key)
			current = current->right;
		else{
			ceiling = current;
			current = current->left;
		}
	}

	return ceiling;
}

TreeNode* FindCeiling(TreeNode *root, int key)  {  
    if(root == NULL)  
        return NULL;  
    if(root->data <= key)  
        return FindCeiling(root->right, key);  
    else{  
        TreeNode *ceiling = FindCeiling(root->left, key);  
        return ceiling ? ceiling : root;  
    }  
}  
