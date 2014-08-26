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
/*
@func: split string  by '/'
@params: path{string}, the path string need to be splitted
@return: vector<string>, the vector contains all opertion on the path or folder name
*/
vector<string> splitString(string path, char delim){
	stringstream ss(path);
	string item;
	vector<string> path_vec;

	while (getline(ss, item, delim)){
		path_vec.push_back(item);
	}

	return path_vec;
}

template<typename Operator>
void tokenize(Operator& op, const char* input, const char* delimiters) {
	const char* s = input;
	const char* e = s;
	while (*e != 0) {
		e = s;
		while (*e != 0 && strchr(delimiters, *e) == 0) ++e;
		if (e - s > 0) {
			op(s, e - s);
		}
		s = e + 1;
	}
}

/*
@func: join the elem of vector into string
*/
string convertToPath(deque<string> path){
	ostringstream stream;

	copy(path.begin(), path.end(), ostream_iterator<string>(stream, "/"));
	string s = stream.str();
	
	return s;
}

/*
@func: get the current path according to relative path and absolute path
*/
string GetPath(string relativePath, string absolutePath){
	if (relativePath.empty())
		return absolutePath;
		
	deque<string>  path_stack;
	// split the absolute path
	vector<string> ab_path = splitString(absolutePath, '/');
	for (vector<string>::iterator itor = ab_path.begin(); itor != ab_path.end(); ++itor){
		path_stack.push_back(*itor);
	}
	
	// split the relative path
	vector<string> re_path = splitString(relativePath, '/');
	for (vector<string>::iterator itor = re_path.begin(); itor != re_path.end(); ++itor){
		if (*itor == ".")
			continue;
		else if (*itor == "..")
			path_stack.pop_back();
		else
			path_stack.push_back(*itor); 
	}
	
	//deque<string> str_queue;
	//while(!path_stack.empty()){
	//	string elem = path_stack.top();
	//	str_queue.push_front(elem);
	//	path_stack.pop();
	//}

	return convertToPath(path_stack);
}
