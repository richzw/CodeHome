/*
有这样一个数组A，大小为n，相邻元素差的绝对值都是1.如： A={4,5,6,5,6,7,8,9,10,9}。 
现在，给定A和目标整数t，请找到t在A中的位置。除了依次遍历，还有更好的方法么？
*/

int find_from_absolute(int arr[], int len, int val){
	int index = 0;

	while(index < len){
		int diff = arr[index] - val;
		if (diff == 0)
			break;
		else
			index += abs(diff);
	}

	return index;
}
