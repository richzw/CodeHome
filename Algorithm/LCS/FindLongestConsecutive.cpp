
int findConsecutive(unordered_map<int, bool>& map, int val, int step){
	int len = 1;

	while (map.find(val) != map.end() && !map.at(val)){
		map.at(val) = true;
		++len;
		val += step;
	}

	return len;
}

int getLongestConsecutive(int nums[], int len){
	unordered_map<int, bool>	map;

	for (int i = 0; i < len; ++i){
		map.insert(make_pair<int, bool>(nums[i], false));
	}

	int max_len = 0;
	for (int i = 0; i < len; ++i){
		if (!map.at(nums[i])){
			map.at(nums[i]) = true;
			int len = findConsecutive(map, nums[i]-1, -1);
			len += findConsecutive(map, nums[i]+1, 1);
			max_len = max(max_len, len);
		}
	}

	return max_len-1;
}
