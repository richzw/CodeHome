
// sort collections
 void insertSort(int a[], int len){
     for (int j = 1; j < len; ++j){
         int key = a[j];
         int i = j - 1;
         while(i >= 0 && a[i] > key){
             a[i+1] = a[i];
             i--;
         }
         a[i+1] = key;
     }
 }

 void insertSort_recursive(int a[], int len){
     if (len <= 1) return;
     insertSort_recursive(a, len-1);
     int key = a[len-1];
     int i = len - 2;
     while(i >= 0 && a[i] > key){
         a[i+1] = a[i];
         --i;
     }
     a[i+1] = key;
 }
