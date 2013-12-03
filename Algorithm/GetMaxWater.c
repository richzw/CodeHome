/*
给定一个正整数数组如[2,5,1,2,3,4,7,7,6]，数组中每个数代表一个墙的高度，如图，​​
问：往墙里倒水，墙之间的水坑总共可以装多少水呢？
​
木桶短板理论：一只木桶盛水的多少，并不取决于桶壁上最高的那块木块，而恰恰取决于桶壁上最短的那块。
此问题同样也是这样的道理，不同的是，此处的短板是相对而言的，畜水的多少由两个邻近的最长的板所决定，且这两个长板不相邻。
如果这是一个递增的数组或是递减的数组或是先增后减的数据，显然是不能装水的,因为最长的板总是在一块的。
如要装水则要求当从左往右遍历数组时，紧邻的右边的数比左边数小，且不会一直小下去；
同样当从右往左遍历数据时，要求紧邻的左边的数据比右边的数小且不会一直小下去。 
假如我们从左至右遍历数组，每个下标畜水的量最多为(目前为止的最大值-当前下标的值)，可问题是此值是不确定，因为右边的长板在哪我们不知道。
​
但是，如果我们指定两个指针分别从数组两端向中间移动，当两个指针相遇时过程结束，在移动的过程中，
比较两个指针处值的大小，值小的一方指针向前移动一位(对左边的指针来说往右是前，对右边的指针来说往左是前)，
如要移动后的值比移动前的值小，则说明此处可以畜水；如果移动后的值比移动前的值大，则此处不能畜水。
如此递归下去，时间复杂度为O(n) ，分析完毕。示例代码如下：​

进一步，把问题稍微改一下，如果水坑不是连续的，不要求求出总的畜水值，而是畜水最多的那个值，要怎么做呢？
分析同上，两个指针分别从两端向中间遍历，相遇时过程结束；对于大小为n的数组，最多可以有 n/2 个不连续的水坑，
当左右指针在移动时，每  当遇到一个新的最大值大值则意味着一个水坑的分界点。
当找出所有的水坑后，再对所有的结果做一次排序(如果仅要最大值是不需要排序的)，就可以了。示例代码如下：
*/
int get_max_water(int arr[], int len){
	int start = 0;
	int stop = len-1;
	int cur_water_left = 0;
	int max_water_left = 0;
	int cur_water_right = 0;
	int max_water_right = 0;
	int max_height_right = arr[stop];
	int max_height_left = arr[start];

	while (start != stop){
		int pre_height = 0;
		if (arr[start] > arr[stop]){
			pre_height = arr[stop];
			--stop;

			if (pre_height < arr[stop] && max_height_right < arr[stop]){
				max_height_right = arr[stop];
				cur_water_right = 0;
			}else{
				cur_water_right += (max_height_right - arr[stop])*1;
				if (cur_water_right > max_water_right)
					max_water_right = cur_water_right;					
			}
		}else{
			pre_height = arr[start];
			++start;

			if (pre_height < arr[start] && max_height_left < arr[start]){
				max_height_left = arr[start];
				cur_water_left = 0;
			}else{
				cur_water_left += (max_height_left - arr[start])*1;
				if (cur_water_left > max_water_left)
					max_water_left = cur_water_left;
			}
		}
	}

	if (arr[start] < max_height_left && arr[start] < max_height_right)
		return max_water_left + max_water_right;
	else
		return max_water_left > max_water_right? max_water_left: max_water_right;
}

// v2
int volume_calcuate(int walls[] , int length){
    int * p_l = &walls[0];
    int * p_r = &walls[length-1];
    int max_l = walls[0];
    int max_r = walls[length-1];

    int total_volume = 0;

    while(p_r > p_l){
        if (max_l < max_r){
            p_l++;
            if (*p_l >= max_l){
                max_l = *p_l;
            }else{
                total_volume += max_l - *p_l;
            }
        }else{
            p_r--;
            if (*p_r >= max_r){
                max_r = *p_r;
            }
            else{
                total_volume += max_r - *p_r;
            }
        }
    }
    return total_volume;
}
