/*
 Q: 给个数组，打乱了，比如：索引 0 1 2 3 4；值 3 2 1 4 0 。数组的值是下次跳的索引位置，
    这样的话数组有环，比如 0 -> 3 -> 4 -> 0, 1 -> 2 -> 1， 求最长环的长度。
*/

int visit_arr(int arr[], int len, int* visit, int val, int* pcount){
  	if (val >= len)
		return 0;

	if (*(visit+val) == 1) // get the end of the circle
		return *pcount;
	else{
		*(visit+val) = 1;
		*pcount += 1;
		visit_arr(arr, len, visit, arr[val], pcount);
	}
}

int find_max_circle_length(int arr[], int len){
	int* pvisit = new int[len+1];
	if (pvisit == NULL)
		return 0;

	memset(pvisit, 0, len+1);

	int max_count = 0;
	for (int index = 0; index < len; ++index){
		if (*(pvisit+index) == 1)
			continue;

		int count = 0;
		if ((count = visit_arr(arr, len, pvisit, arr[index], &count)) > max_count)
			max_count = count;
	}

	delete[] pvisit;
	return max_count;
}
