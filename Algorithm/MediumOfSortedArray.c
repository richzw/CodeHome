/*
There are two sorted arrays A and B of size m and n respectively. 
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/
double findMediumBase1(int med, int arr[], int len){
	if (len == 1)
		return (med+arr[0])/2.0;

	if (len%2 == 0){
		int a = arr[len/2-1], b = arr[len/2];
		if (med <= a)
			return a;
		else if (med <= b)
			return med;
		else
			return b;
	}else{
		int a = arr[len/2-1], b = arr[len/2], c = arr[len/2+1];
		if (med < a)
			return (a+b)/2.0;
		else if (med > c)
			return (b+c)/2.0;
		else
			return (med+b)/2.0;
	}
}

double findMediumBase2(int med1, int med2, int arr[], int len){
	if (len%2 == 0){
		int a = (((len/2-2) >= 0)?arr[len/2-2]:INT_MIN);
		int b = arr[len/2-1];
		int c = arr[len/2];
		int d = (((len/2+1) <= len-1)?arr[len/2+1]:INT_MAX);

		if (med2 < a)
			return (b+ max(a, med2))/2.0;
		else if (med1 < b)
			return (b + min(c, med2))/2.0;
		else if (med1 >= c)
			return (c + min(med1, d))/2.0;
		else if (med2 >= c)
			return (c + max(med1, b))/2.0;
		else
			return (med1+med2)/2.0;
	}else{
		int a = arr[len/2-1],  b = arr[len/2], c = arr[len/2+1];
		
		if (med2 <= b)
			return max(med2, a);
		else if (med1 >= b)
			return min(med1, c);
		else
			return b;
	}
}

double findMediumSingleArray(int arr[], int len){
	if (len < 0)
		return 0;

	return (len%2 == 0)? (arr[len/2-1]+arr[len/2])/2.0:arr[len/2];
}

double findMediumSortedArrays(int a[], int aLen, int b[], int bLen){
	if (aLen + bLen < 1)
		return 0;
	if (aLen == 0)
		return findMediumSingleArray(b, bLen);
	else if (bLen == 0)
		return findMediumSingleArray(a, aLen);
	else if (aLen == 1)
		return findMediumBase1(a[0], b, bLen);
	else if (bLen == 1)
		return findMediumBase1(b[0], a, aLen);
	else if (aLen == 2)
		return findMediumBase2(a[0], a[1], b, bLen);
	else if (bLen == 2)
		return findMediumBase2(b[0], b[1], a, aLen);

	int i = aLen/2, j = bLen/2, k;
	if (a[i] < b[j]){
		k = (aLen%2 == 0)? min(i-1, bLen-j-1): min(i, bLen-j-1);
		return findMediumSortedArrays(a+k, aLen-k, b, bLen-k);
	}else {
		k = (bLen%2 == 0)? min(aLen-i-1, j-1): min(aLen-i-1, j);
		return findMediumSortedArrays(a, aLen-k, b+k, bLen-k);
	}
}
