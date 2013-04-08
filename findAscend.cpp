//Question: Given a array of integers , find 3 indexes i, j, k such that, i<j<k and a[i] < a[j]< a[k]. 
//Could you find possible O(n) algorithm?

//solution: use one additional index array that record the which element of the array bigger than itself.

/*
* @func: find the ascends element from array
* @params: arr{array}, the given array,
*          len{int}, the length of array
*         pos{int}, the first position that finding the ascending elements 
*/
const int ARRLEN = sizeof(arr)/sizeof(arr[0]);

 void findAscend_(int arr[], int len, int pos){
     int index_array[ARRLEN] = {0};
     int current_max = 0;
     int current_max_index = 0;
     if (arr == NULL || pos >= len)
             return ;

     //initialize the index array. traverse the array from back to front
     for (int index = len - 1; index >= 0; --index){
         if (arr[index] > current_max){
             current_max_index = index;
             current_max = arr[index];
         }
         index_array[index] = current_max_index;
     }

     int current = arr[pos];
     for (int index = pos; index < len - 1; ++index){
         if (arr[index] > current && index_array[index] > index)
         {
             cout << "the ascends are: " << current << " "
                     << arr[index] << " "
                     << arr[index_array[index]] << endl;
             return;
         }
     }
 }
