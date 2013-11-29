/*
翻译数字串，类似于电话号码翻译：给一个数字串，比如12259，映射到字母数组，比如，
1 -> a， 2-> b，... ， 12 -> l ，... 26-> z。那么，12259 -> lyi 或 abbei 或 lbei 或 abyi。输入一个数字串，
判断是否能转换成字符串，如果能，则打印所以有可能的转换成的字符串。

我们这里来分析一下这个题目的分析思路。看完这个描述，我们应该注意到一下的细节：
        * 映射是在[1,26]这个范围内数字
        * 输入的字符串是否包括0或者负数？
充分理解题目的含义、目的之后，很直接的就可以想到这个题目可以用递归解决。如原题中的例子：12259，它有两个递归的子问题，
（1）2259和（12）259，前面的括号表示是否能够通过映射表翻译。同理每一个子问题，都会表示为这样的两个子问题。
接下来，我们考虑（1）2259的两个子问题：
        1. （12）259
        2. （122）59
大家有注意到，第一个和12259的一个子问题重复了。大家是否对这个似曾相识呢？当大家把递归过程的树形结构画出来，
会发现更多的重复子问题，这就给了我们改进的空间，只需要取消这些重复计算就可以了。
第一个方法就是记忆法，将计算过的结果缓存起来，这样可以后续接着使用。但是更近一步，我们是可以采用动态规划的方法的。
很多同学也都直接的想到了。
*/
string map_string_recur(string number_str, int idx, string str, unordered_multimap<string, string>& str_map, unordered_map<int, char> char_map){
	if (idx >= number_str.length()){
		cout << str.c_str() << endl;
		return str;
	}

	string ret_str;
	unordered_multimap<string, string>::iterator itor = str_map.find(number_str.substr(idx));
	if (itor != str_map.end()){
		str += itor->second;
		cout << str.c_str() << endl;
		return str;
	}else{
		if (number_str.length() - idx >= 2){
			// 2 numbers case
			int num = atoi(number_str.substr(idx, 2).c_str());
			if (num > 0 && num < 27){
				str.push_back(char_map[num]);
				ret_str = map_string_recur(number_str, idx+2, str, str_map, char_map);
				str_map.insert(make_pair<string, string>(number_str.substr(0, idx+2), str));
				if (ret_str.length() > str.length())
					str_map.insert(make_pair<string, string>(number_str.substr(idx+2), ret_str.substr(str.length())));
				str.pop_back();
			}
		}
		// 1 number case
		int n = atoi(number_str.substr(idx, 1).c_str());
		str.push_back(char_map[n]);
		ret_str = map_string_recur(number_str, idx+1, str, str_map, char_map);
		str_map.insert(make_pair<string, string>(number_str.substr(0, idx+1), str));
		if (ret_str.length() > str.length())
			str_map.insert(make_pair<string, string>(number_str.substr(idx+1), ret_str.substr(str.length())));
	}

	return ret_str;
}

string number_map_string(string number_str){
	unordered_map<int, char> char_map; // 'a' - 'z' map to 1-26
	unordered_multimap<string, string> str_map; // store the results
	string str = "";

	for (int i = 1; i < 27; ++i){
		char_map[i] = 'a'+i-1;
	}

	return map_string_recur(number_str, 0, str, str_map, char_map);
}
