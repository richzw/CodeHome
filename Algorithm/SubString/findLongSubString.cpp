/*
//给定一个数组，数组中只包含0和1。请找到一个最长的子序列，其中0和1的数量是相同的。
//例1：10101010 结果就是其本身。
//例2：1101000 结果是110100
原来是0和1的串，我们将0都换为-1。这样题目目标就变成，找到一个最长的子串，子串数字和是0。
如果DP[i]==DP[j]，i 一种方法，我们用map保存DP的值到位置的映射，如下表：
上面的这个思路，时间复杂度是O(n),空间复杂度也是O(n).
*/

//O(n^2) time O(n) space
string find_long_sub_seq(int arr[], int len){
	int* pt = new int[len];
	string str = "";

	if (pt != NULL){
		// mark 0 to -1
		for (int index = 0; index < len; ++index){
			if (arr[index] == 0)
				arr[index] = -1;
		}

		// get the sub sum of array
		*pt = arr[0];
		for (int index = 1; index < len; ++index){
			*(pt+index) = *(pt+index-1)+arr[index];
		}

		// tranverse array from tail
		int end = 0, begin = 0;
		for (int index = len-1; index >= 0; --index){
			if (*(pt+index) == 0){
				end = index;
				break;
			}
		}

		for (int i = 0; i < len; ++i){
			for (int j = i; j < len; ++j){
				if ((arr[j] - arr[i]) == 0 && (j-i)>(end-begin)){
					end = j;
					begin = i;
				}
			}
		}

		for (int index = begin; index <= end; ++index){
			str += to_string((long double)arr[index]);
		}

		delete[] pt;
	}
	return str;
}


//better solution, O(n) time, and O(n) space
string find_long_sub_seq_improve(int arr[], int len){
	int* pt = new int[len];
	string str = "";

	if (pt != NULL){
		// mark 0 to -1
		for (int index = 0; index < len; ++index){
			if (arr[index] == 0)
				arr[index] = -1;
		}

		// get the sub sum of array
		*pt = arr[0];
		for (int index = 1; index < len; ++index){
			*(pt+index) = *(pt+index-1)+arr[index];
		}

		unordered_multimap<int, int> hmap;
		for (int index = 0; index < len; ++index){
			hmap.insert(make_pair<int, int>(*(pt+index), index));
		}

		int begin = 0, end = 0;
		int max_dis = 0;
		int cnt = hmap.bucket_count();
		for (int c = 0; c < cnt; ++c){
			if (hmap.bucket_size(c) == 0)
				continue;

			auto iter = hmap.begin(c);
			int start = iter->second;
			for (; iter != hmap.end(c); ++iter){
				if (iter->second - start > max_dis){
					max_dis = iter->second - start;
					begin = start;
					end = iter->second;
				}
			}
		}

		for (int index = begin; index <= end; ++index){
			str += to_string((long double)arr[index]);
		}

		delete[] pt;
	}
	return str;

}
