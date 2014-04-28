//Q: select m numbers from N numbers randomly.

//version 1
// shuffle, then the first m numbers are the answer.

//version 2
// divide N with M blocks, select one number from them,
// for the remain numbers, select one randomly then replace one of those m-1 numbers
void selectRandomM(int rand[], int rlen, int arr[], int mlen){
	int dividor = mlen/rlen;
	int ridx = 0;
	int idx = 0;
	int idx_rand = 0;
	
	for (idx = 0; idx < mlen; idx+=dividor){
		srand(time(NULL));
		idx_rand = rand()%dividor;
		rand[ridx++] = arr[idx_rand+idx*dividor];
	}
	
	if (mlen%rlen){
		idx_rand = rand()%(mlen-idx+dividor) + idx - dividor;
		rand[rand()%(rlen-1)] = arr[idx_rand];
	}
}

// version 3
//随机获取元素，可以使用rand() % 数组长度；
//其次，要保证元素的不重复获取，只需将获取的元素从原数组中移除即可，
//但是每次都进行删除操作，需要频繁的移动数组元素，其复杂度很高；
//现在，我们换一种思路，将获取的元素与原数组最后的元素进行交换，再将数组的长度减一
void swap(int* a, int* b){
	int tmp = *b;
	*a = *b;
	*b = tmp;
}

void selectRandomM(int rand[], int rlen, int arr[], int mlen){
	int ridx = 0;
	
	while (ridx < rlen){
		srand(time(NULL));
		idx_rand = rand()%mlen;
		swap(arr+mlen-1, arr+idx_rand);
		rand[ridx++] = arr[arr+mlen-1];
		mlen--;
	}
}
