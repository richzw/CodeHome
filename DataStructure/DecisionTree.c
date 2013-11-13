struct tree_node{
	char data;
	tree_node* left;
	tree_node* right;
};

tree_node* insert_tree(tree_node* node, char ch, string code){
	if (code.length() == 0)
		return node;

	if (node == NULL){
		node = (tree_node*)malloc(sizeof(tree_node));
		node->left = NULL;
		node->right = NULL;		
		if (code.length() > 1) 
			node->data = ' ';
		else{
			node->data = ch;
			return node;
		}
	}

	if (code.at(1) == '.'){
		node->left = insert_tree(node->left, ch, code.substr(1));	
	}else{
		node->right = insert_tree(node->right, ch, code.substr(1));
	}

	return node;
}

tree_node* build_decision_tree(map<char, string> morse_code){
	tree_node* root = (tree_node*)malloc(sizeof(tree_node));
	root->data = '*';
	root->left = NULL;
	root->right = NULL;

	for (map<char, string>::iterator itor = morse_code.begin(); 
		itor != morse_code.end(); ++itor){
		if (itor->second.at(0) == '.')
			root->left = insert_tree(root->left, itor->first, itor->second);
		else
			root->right = insert_tree(root->right, itor->first, itor->second);
	}

	return root;
}
