//aka, Cocktail sort, also known as bidirectional bubble sort,
/*
Cocktail sort is a slight variation of bubble sort. It differs in that instead of repeatedly passing through the list 
from bottom to top, it passes alternately from bottom to top and then from top to bottom. 
It can achieve slightly better performance than a standard bubble sort. 
The reason for this is that bubble sort only passes through the list in one direction and therefore can only 
move items backward one step each iteration.
*/
void shaker_sort(int arr[], int len){
	assert(arr != NULL && len > 0);
	int cur_min = 1;
	int cur_max = len-1;
	bool moved = false;
	
	do {
		moved = false;
		for (int i = cur_min; i < cur_max; ++i){
			if (arr[i] < arr[i-1]){
				int tmp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = tmp;
				moved = true;
			}
		}
		cur_max--;
		for (int i = cur_max; i >= cur_min; --i){
			if (arr[i] < arr[i-1]){
				int tmp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = tmp;
				moved = false;				
			}
		}
		cur_min++;
		
		if (!moved)
			break;
	} while(moved);
}
