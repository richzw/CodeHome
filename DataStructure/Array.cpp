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

/*
 * @func: Get the min distance between two element of the array
 */
int comp(const void* pa, const void* pb){
    return (*(int*)pa - *(int*)pb);
}

int findMinDistance(int arr[], int len){
    if (arr == NULL || len <= 0)
            return -1;

    qsort(arr, len, sizeof(int), comp);

    int min_distance = INT_MAX;
    for (int index = 0; index < len - 1; ++index){
        int distance = arr[index + 1] - arr[index];
        if (distance < min_distance)
                min_distance = distance;
    }

    return min_distance;
}

/*
 *@func: find the common element between two ordered arrays.
 */
void findCommonElem(int a[], int b[], int len){
  int i = 0, j = 0;
  while (i < len && j < len)
  {
      if (a[i] == b[j]){
          cout << a[i] << " ";
          ++i, ++j;
      }else if (a[i] < b[j]){
          ++i;
      }else
          ++j;
  }
  cout << endl;
}
/*
 *@func: find the element with odd count from array
 */
int findElemOfOddCnt(int arr[], int len)
{
  if (arr == NULL || len <= 0)
          return -1;
  int val = arr[0];
  for (int index = 1; index < len; ++index){
      val ^= arr[index];
  }
  return val;
}
/*
 *@func: Get the max sub sum of array. from Program Pearling
 */
int maxSubSum(int a[], int n){
  int cur_sum = 0;
  int max_sum = 0;
  for (int index = 0; index < n; ++index){
      if (cur_sum + a[index] < 0)
          cur_sum = 0;
      else{
          cur_sum += a[index];
          max_sum = max(max_sum, cur_sum);
      }
  }
  return max_sum;
}

/*
 *@func: Get the max product of array.
 *       specially for negative number handling.
 */
int maxSubProduct(int arr[], int n){
  int cur_product = 1;
  int cur_product_neg = 1; // min negative product.
  int max_product = 1;
  for (int index = 0; index < n; ++index){
      if (arr[index] > 0 ){
          cur_product *= arr[index];
          cur_product_neg = min(cur_product_neg, 1);
      }else if (arr[index] == 0){
          cur_product = 1;
          cur_product_neg = 1;
      }else {
          int tmp = cur_product;
          cur_product = max(cur_product_neg * arr[index], 1);
          cur_product_neg = tmp * arr[index];
      }
      max_product = max(max_product, cur_product);
  }
  return max_product;
}
