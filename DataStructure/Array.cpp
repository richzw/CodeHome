
/*
* @fun: Get the sum of array
*/
int sum(int arr[], int n)
{
   return (n == 0)? 0 : arr[n-1] + sum(arr, n-1);
}
/*
* @func: Get the min value and max value of the array
* @params: l {int}, the left boundary of the array
*          r {int}, the right boundary of the array
*          maxValue {int}, the max value of the array.
*          minValue {int}, the min value of the array
*/
void MaxandMin(int arr[], int l, int r, int& maxValue, int& minValue)
{
   if (arr == NULL || l > r)
       return;
   if (l == r){ // only one element
       maxValue = arr[l];
       minValue = arr[r];
       return;
   }else if (l + 1 == r) { // for two element between l and r
       if (arr[l] > arr[r]){
           maxValue = arr[l];
           minValue = arr[r];
       }else{
           maxValue = arr[r];
           minValue = arr[l];
       }
       return;
   }
   int mid = l + (r - l)/2;
   int lmin = 0, lmax = 0;
   MaxandMin(arr, l, mid, lmax, lmin);
   int rmin = 0, rmax = 0;
   MaxandMin(arr, mid, r, rmax, rmin);
   maxValue = max(lmax, rmax);
   minValue = min(lmin, rmin);
}

/*
 * @func: Get the modal of the array, the frequency of this modal is more than half of array length
 */
int findModal(int arr[], int len){
    assert(arr != NULL);
    int modal = arr[0];
    int cnt = 1;

    for (int index = 1; index < len; ++index){
        if (arr[index] == modal)
            ++cnt;
        else{
            --cnt;
            if (cnt == 0){
                modal = arr[index];
                cnt = 1;
            }
        }
    }

    if (cnt > 0)
            return modal;
    else
            return -1;
}
