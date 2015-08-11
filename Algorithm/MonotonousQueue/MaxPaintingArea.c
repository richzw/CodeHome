/*
问题：有n幢建筑，其高度分别为H1，...，Hn，其宽度为1，且这些建筑紧靠在一起，当前需要在这些建筑上刷一个非常大的矩形广告，
求矩形广告的最大值
*/

// naive method, O(N^3)
static int get_min(int *s, int start, int end)
{
    int i, min = s[start];

    for (i = start;i <= end;i++) {
        if (min > s[i])
            min = s[i];
    }
    return min;
}

int continous_sum_o3(int *s, int n)
{
    int i, j;
    int min, max = s[0];

    for (i = 0;i <= n - 1;i++) {
        for (j = i;j <= n - 1;j++) {
            min = get_min(s, i, j);
            if (max < min * (j - i + 1))
                max = min * (j - i + 1);
        }
    }

    return max;
}

// O(N^2)
int GetMaxMatrix(int arr[], int len){
	int min = max = arr[0];
	
	for (int i = 0; i < len; ++i){
		min = arr[i];
		if (max < arr[i])
			max = arr[i];
		for (int j = i; j < len; ++j){
			min = std::min(min, arr[j]);
			if (max < min*(j-i+1))
				max = min*(j-i+1);
		}
	}
	
	return max;
}

// monotonous queue
/*
考虑构造一个单调非递减队列，从左至右，依次加入到队列中，肯定会有元素出队列，设当前要插入的数为a，要出队列的数为b，
必有b>=a，则b向右能到达的最远距离就是b-a。注意在求解时，让0先入队列，这样保证每个数据都会出队列。同理，左极限也可求出。
*/
int GetMaxMatrix_monqueue(int arr[], int len){
    int i, max, val;
    int start = 0, end = -1;
    int *rn = NULL, *ln = NULL, *P = NULL;

    rn = malloc(sizeof(unsigned int) * n);
    ln = malloc(sizeof(unsigned int) * n);
    P = malloc(sizeof(unsigned int) * n);

    /* calc right continuous block */
    for (i = 0;i < n;i++) {
        for (;end >= start && s[i] < s[P[end]];end--) {
            rn[P[end]] = i;
        }
        end++;
        P[end] = i;
    }
    for (i = start;i <= end;i++) {
        rn[P[i]] = n;
    }


    /* calc left continuous block */
    for (i = n - 1;i >= 0;i--) {
        for (;end >= start && s[i] < s[P[end]];end--) {
            ln[P[end]] = i;
        }
        end++;
        P[end] = i;
    }
    for (i = start;i <= end;i++) {
        ln[P[i]] = -1;
    }

    /* determin the max block */
    max = s[0];
    for (i = 0;i < n;i++) {
        val = s[i] * (rn[i] - ln[i] - 1);
        if (val > max)
            max = val;
    }

	return max;
}
