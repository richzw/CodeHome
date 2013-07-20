/*
Q: 有k个有序的数组，请找到一个最小的数字范围。使得这k个有序数组中，每个数组都至少有一个数字在该范围中。 例如：

1: 4, 10, 15, 24, 26
2: 0, 9, 12, 20
3: 5, 18, 22, 30
所得最小范围为[20,24]，其中，20在2中，22在3中，24在1中。
*/

/*
通过归并排序的思想，确保每次都是k个来自不同的数组的元素进行比较，得到最大值、最小值。
就可以得到一个范围，包含了所有数组中的数字。

这个题的著名变种是从网页中产生包含所有查询词的最小的摘要。
*/

typedef struct RetVal{
  int begin;
	int end;
}RetVal;

int max_three(int a, int b, int c){
	return (a>b)?((a>c)?a:c):((b>c)?b:c);
}
int min_three(int a, int b, int c){
	return (a<b)?((a<c)?a:c):((b<c)?b:c);
}

RetVal getMinRangeFromOrderedArrays(int a1[], int a2[], int a3[], int len){
	int* p1 = a1;
	int* p2 = a2;
	int* p3 = a3;
	int range = max_three(*p1, *p2, *p3) - min_three(*p1, *p2, *p3);

	RetVal ret;
	ret.begin = min_three(*p1, *p2, *p3);
	ret.end = max_three(*p1, *p2, *p3);
	while (--len >= 0){
		if (*p1 < *p2 && *p1 < *p3)
			++p1;
		else if (*p2 < *p1 && *p2 < *p3)
			++p2;
		else if (*p3 < *p1 && *p3 < *p2)
			++p3;
		
		if ((max_three(*p1, *p2, *p3) - min_three(*p1, *p2, *p3)) < range){
			range = max_three(*p1, *p2, *p3) - min_three(*p1, *p2, *p3);
			ret.begin = min_three(*p1, *p2, *p3);
			ret.end = max_three(*p1, *p2, *p3);
		}
	}

	return ret;
}
