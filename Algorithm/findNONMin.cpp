/*
   Q: Given a disorderly array of integers, how to find a smallest value greater than 0, 
      and doesnot exist in this integer array. 
      For example, [1,2,0] return 3, [3,4, -1,1] returns 2. Preferably O (1) space, and O (n) time
*/

int findNonMin(int arr[], int len){

     // make the number into correct position
     for (int index = 0; index < len; ++index){
         while (arr[index] != index &&
                arr[index] < len &&
                arr[index] > 0){
            // fix one bug here...
            if (arr[arr[index]] == arr[index])
               break;
             int tmp = arr[arr[index]];
             arr[arr[index]] = arr[index];
             arr[index] = tmp;
         }
     }

     // find the NonMin number
     for (int index = 1; index < len; ++index){
         if (arr[index] == index)
             continue;
         return index;
     }

     return len + (arr[0] == len);
 }

 int main(){
     int array[] = {4, 3, 2, 1, 5};
     cout << "the min non exist number is " << findNonMin(array, sizeof(array)/sizeof(array[0])) << endl;

     return 0;
 }
