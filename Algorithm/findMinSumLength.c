/*
设置索引i，j指向第一个整数：
	1. ++j，直到sum[j]-sum[i]>S，这里不需要额外保存sum，为了方便说明。记录子序列长度
	2. ++i，如果sum[j]-sum[i]>S，更新最小子序列长度。直到sum[j]-sum[i]<=S。
	3. ++j，直到sum[j]-sum[i]>S。重复上面的两步，直到数组遍历完毕。
*/

int find_min_length(int arr[], int len, int sum){
	int i = 0, j = 0;
	int min_len = len;
	int sub_sum = 0;

	while(j < len){
		sub_sum += arr[j];
		while (sub_sum > sum){
			sub_sum -= arr[i];
			if (sub_sum == sum && j - i < min_len){
				min_len = j - i;
			}else if(sub_sum < sum){
				break;
			}
			++i;
		}
		++j;
	}

	return min_len;
}
