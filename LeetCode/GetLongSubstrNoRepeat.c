/*
Given a string, find the length of the longest substring without repeating characters. 
For example, the longest substring without repeating letters for “abcabcbb” is “abc”, which the length is 3. 
For “bbbbb” the longest substring is “b”, with the length of 1.
*/

// Datastructure: hashmap + two pointers
int GetLongSubstrNoRepeat(string s){
	int len = s.length();
	int fast = 0, slow = 0;
	int max_len = 0;
	bool char_map[256] = {false};

	while (fast < len){
		if (char_map[s[fast]]){ //exist before
			max_len = max(max_len, fast-slow);
			while (s[fast] != s[slow]){ // reset the chars before
				char_map[s[slow]] = false;
				++slow;
			}
			++slow; // fixme:
			++fast;
		}else{
			char_map[s[fast]] = true;
			++fast;
		}
	}

	return max(max_len, len-slow); // fixme
}
