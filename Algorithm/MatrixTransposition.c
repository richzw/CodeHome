
// Matrix Transposition.
// round-robin queue method...
// time complexity O(n), space complexity O(n)

void cyclic_shift(int arr[], int from, int to){
	if (from <= to)
		return;
	int tmp = arr[from];
	for (int i = from-1; i >= to; --i){
		arr[i+1] = arr[i];
	}
	a[to] = tmp;
}

void MatixTransposition(int matrix[][], int width, int height){
	int shift_to = 0;
	int shift_from = 0;

	for (int j = 0; j < width; ++j)
		for (int i = 0; i < height; ++i){
			shift_to = j*height+i;
			shift_from = shift_to + i*(width-j) - i;
			cyclic_shift(matrix, shift_from, shift_to);
		}
}
