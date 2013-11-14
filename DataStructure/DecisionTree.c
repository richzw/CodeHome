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

	if (code.at(0) == '.'){
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

int main(){
	map<char, string> morse_code;
	morse_code.insert(make_pair('A', ".-"));
	morse_code.insert(make_pair('B', "-..."));
	morse_code.insert(make_pair('C', "-.-."));
	morse_code.insert(make_pair('D', "-.."));
	morse_code.insert(make_pair('E', "."));
	morse_code.insert(make_pair('F', "..-."));
	morse_code.insert(make_pair('G', "--."));
	morse_code.insert(make_pair('H', "...."));
	morse_code.insert(make_pair('I', ".."));
	morse_code.insert(make_pair('J', ".---"));
	morse_code.insert(make_pair('K', "-.-"));
	morse_code.insert(make_pair('L', ".-.."));
	morse_code.insert(make_pair('M', "--"));
	morse_code.insert(make_pair('N', "-."));
	morse_code.insert(make_pair('O', "---"));
	morse_code.insert(make_pair('P', ".--."));
	morse_code.insert(make_pair('Q', "--.-"));
	morse_code.insert(make_pair('R', ".-."));
	morse_code.insert(make_pair('S', "..."));
	morse_code.insert(make_pair('T', "-"));
	morse_code.insert(make_pair('U', "..-"));
	morse_code.insert(make_pair('V', "...-"));
	morse_code.insert(make_pair('W', ".--"));
	morse_code.insert(make_pair('X', "-..-"));
	morse_code.insert(make_pair('Y', "-.--"));
	morse_code.insert(make_pair('Z', "--.."));

	build_decision_tree(morse_code);	
	
	return 0;
}
