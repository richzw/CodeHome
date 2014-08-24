/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/

/*
@func: split string  by '/'
@params: path{string}, the path string need to be splitted
@return: vector<string>, the vector contains all opertion on the path or folder name
*/
vector<string> splitString(string path){
	
}

string convertToPath(stack<string> path){
	string path_str;
	
	while(!path.empty()){
		path_str += path.peek() + "\";  //TODO: add before??
	}
	
	return path_str;
}

/*
@func: get the current path according to relative path and absolute path
*/
string GetPath(string relativePath, string absolutePath){
	if (relativePath == NULL)
		return absolutePath;
		
	stack<string>  path_stack;
	// split the absolute path
	vector<string> ab_path = splitString(absolutePath);
	for (vector<string>::iterator itor = ab_path.begin(); itor != ab_path.end(); ++itor){
		path_stack.push(*itor);
	}
	
	// split the relative path
	vector<string> re_path = splitString(relativePath);
	for (vector<string>::iterator itor = re_path.begin(); itor != re_path.end(); ++itor){
		if (*itor == ".")
			continue;
		else if (*itor == "..")
			path_stack.pop();
		else
			path_stack.push(*itor);
	}
	
	return convetToPath(path_stack);
}
