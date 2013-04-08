


 const int LEN = 3;
 struct node{
     int val;
     int seq;
 }monoto_Q[LEN];
/*
* @func: monotonous queue implementation
* @params: arr{array}, the data array
*          len{int}, the length of data array
*          qSize{int}, the size of monotonous queue
*/
 void _MonotonousQueue(int arr[], int len, int qSize){
     if (arr == NULL || len <= LEN)
         return;
     int index = 0, tail = 0, head = 1;

     //initialize the monotonous queue
     for (index = 0; index < qSize; ++index){
         while (head <= tail && arr[index] > monoto_Q[tail].val){
                 --tail;
         }
         monoto_Q[++tail].val = arr[index];
         monoto_Q[tail].seq = index;
     }

     //handle the data array
     for (index = qSize - 1; index < len; ++index){
         while (head <= tail && arr[index] > monoto_Q[tail - 1].val){
                 --tail;
         }
         monoto_Q[++tail].val = arr[index];
         monoto_Q[tail].seq = index;
         while (index - monoto_Q[head].seq > qSize - 1)
                 ++head;
         cout << monoto_Q[head].val << " ";
     }
     cout << endl;
 }
