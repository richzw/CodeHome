// 1. Given a single-linked list containing N items, rearrange the items uniformly at random.

/*
* @func: shuffle with {1, 2, 3} and {7, 13, 1} should yield {1, 7, 2, 13, 3, 1}
*        this is perfect shuffle.
*/
node* shuffle(node* a, node* b){
  node dummy;
	node* pdummy = &dummy;
	pdummy->next = NULL;

	while(true){
		if (a == NULL){
			pdummy->next = b;
			break;
		}else if (b == NULL){
			pdummy->next = a;
			break;
		}else{
			pdummy->next = a;
			pdummy = a;
			a = a->next;
			pdummy->next = b;
			pdummy = b;
			b = b->next;
		}
	}
	return (dummy.next);
}

/*
* @func: Given a singly-linked list containing N items, rearrange the items uniformly at random
*/
extern "C" __declspec(dllexport) node* shufflelist(node* head){
	node* pfast = head;
	node* pslow = head;
	node* pdummy = NULL;

	//pfast move 2x speed than pslow, pslow point to the middle of linked list
	while(pfast != NULL && pfast->next != NULL){
		pslow = pslow->next;
		pfast = pfast->next->next;
	}

	//split the linked list into two seperate linked list.
	//their headers are head and pdummy repectively.
	pdummy = pslow->next;
	pslow->next = NULL;

	return shuffle(head, pdummy);
}

//2. random array. please refer to http://coolshell.cn/articles/8593.html

const size_t MAXLEN = 10;
int TestArr[MAXLEN] = {1,2,3,4,5,6,7,8,9,10};

int compare(const void* a, const void* b)
{
   return rand()%3 - 1;
}
void ShuffleArray_Sort(int arr[], int len)
{
   qsort((void*)arr, (size_t)len, sizeof(int), compare);
}

static int RecurArr[MAXLEN] = {0};
static int cnt = 0;
void ShuffleArray_Recur_tmp(int arr[], int len){
   if (cnt > MAXLEN || len <= 0)
           return;
   int pos = rand()%len;
   RecurArr[cnt++] = arr[pos];
   if (len == 1) return;
   ShuffleArray_Recur_tmp(arr, pos);
   ShuffleArray_Recur_tmp(arr+pos+1, len - pos - 1);
}
void ShuffleArray_Recursive(int arr[], int len){
   memset(RecurArr, 0, sizeof(RecurArr));
   cnt = 0;
   ShuffleArray_Recur_tmp(arr, len);
   memcpy(arr, RecurArr, len);
}

int RNG(int small, int large);
void poker_shuffle(int a[], int len){
	for (int i = len; i > 0; --i){
		int rand = RNG(0, i);
		std::swap(a[i], a[rand]);
	}
}

//
void ShuffleArray_Fish_Ya(int arr[], int len)
{
   int index = len, j;
   int tmp = 0;
   if (index <= 1)
           return;
   while(index--){
       j = rand()%(index+1);
       tmp = arr[j];
       arr[j] = arr[index];
       arr[index] = tmp;
   }
}
