/*
A long array A[] is given to you. There is a sliding window of size w which is moving from the very left of the array to the very right. 
You can only see the w numbers in the window. Each time the sliding window moves rightwards by one position. Following is an example:
The array is [1 3 -1 -3 5 3 6 7], and w is 3.
*/

// heap method
void get_max_window(int A[], int len, int w, int B[]){
	priority_queue<pair<int, int> > pq;

	// initialize the window
	for (int i = 0; i < w; ++i){
		pq.push(make_pair(A[i], i));
	}

	for (int i = w; i < len; ++i){
		pair<int, int> elem = pq.top();
		B[i-w] = elem.first;

		if (elem.second <= i - w){
			pq.pop();
		}
		pq.push(make_pair(A[i], i));
	}

	B[len-w] = pq.top().first;
}
