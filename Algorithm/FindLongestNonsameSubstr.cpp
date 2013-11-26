/*
由26个小写字母组成的字符串str，在str中查找最长不含相同字符的连续子串。​
如abcacfrar，为acfr。​

最笨的方法，我们可以遍历所有的子串，然后找出未出现重复字母的子串，找出这些子串中最长的长度即可，
这样的时间复杂度是O(n^2)。分析上面的方法，其实我们做了很多的重复运算，比如当我们判断到abca已经开始包含重复的字母了，
其实已经隐含了从第二个字母开始bca中一定不包含相同的字母，上面的方法中并没有充分利用这个特性，因此我们可以对算法进行改进。​
这个题还有一点就是需要记录字母是否在子串中已经出现过，这个我们可以通过哈希的方法来实现，这个题中限定了26个小写字母，
我们就可以比较巧妙地实现哈希算法。直接用一个int数组来记录上次该字符出现的位置pos[c-'a']即对应c的记录位置。
*/
string find_longest_substring(string str){
	int begin = 0, end = 0;
	int len = str.size();
	int max_len = 0;
	int cur_len = 0;
	unordered_map<char, int> hmap;

	// init hash map
	for (char ch = 'a'; ch <= 'z'; ++ch){
		hmap[ch] = -1;
	}

	for (int i = 0; i < len; ++i){
		++cur_len;
		if (hmap[str[i]] != -1){
			if (cur_len > max_len){
				max_len = cur_len;
				end = i;
				begin = hmap[str[i]];
				cur_len = 1;
			}
			hmap[str[i]] = i;
		}else{
			hmap[str[i]] = i;
		}
	}

	return str.substr(begin, end-begin);
}
