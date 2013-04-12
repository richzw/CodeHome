/*
* Q: Given an ordered array, find the min absolute value.
*/

/*
* binary search
*/
int findMin_binary(int arr[], int left, int right){
   if (NULL == arr)
           return 0;
   while(left < right){
           if (arr[left] > 0)
                   return arr[left];
           if (arr[right] < 0)
                   return arr[right];
           if (right - left == 1){
                   return abs(arr[left]) > abs(arr[right])? (arr[right]) : (arr[left]);
           }
           int mid = (left & right) + ((left ^ right) >> 1);
           if (arr[mid] > 0){
                   right = mid;
           }else{
                   left = mid;
           }
   }
}
/*
* Ternary search  http://en.wikipedia.org/wiki/Ternary_search
*/
int findMin_ternary(int arr[], int left, int right){
   if (NULL == arr)
           return 0;
   while(left < right){
           if (arr[left] > 0)
                   return arr[left];
           if (arr[right] < 0)
                   return arr[right];
           if (right - left == 2){
                   int mid = (left + right) >> 1;
                   int less_min = abs(arr[left]) > abs(arr[right])? (arr[right]) : (arr[left]);
                   return abs(arr[mid]) > abs(less_min) ? less_min : arr[mid];
           }
           int left_third = (2*left + right)/3;
           int right_third = (left + 2*right)/3;
           if(abs(arr[left_third]) > abs(arr[right_third]))
                   left = left_third;
           else
                   right = right_third;
   }
}
 
double phi = (1 + Math.sqrt(5)) / 2;
double resphi = 2 - phi;
 
// a and c are the current bounds; the minimum is between them.
// b is a center point
// f(x) is some mathematical function elsewhere defined
// a corresponds to x1; b corresponds to x2; c corresponds to x3
// x corresponds to x4
public double goldenSectionSearch(double a, double b, double c, double tau) {
    double x;
    if (c - b > b - a)
      x = b + resphi * (c - b);
    else
      x = b - resphi * (b - a);
    if (Math.abs(c - a) < tau * (Math.abs(b) + Math.abs(x))) 
      return (c + a) / 2; 
    assert(f(x) != f(b));
    if (f(x) < f(b)) {
      if (c - b > b - a) return goldenSectionSearch(b, x, c, tau);
      else return goldenSectionSearch(a, x, b, tau);
    }
    else {
      if (c - b > b - a) return goldenSectionSearch(a, b, x, tau);
      else return goldenSectionSearch(x, b, c, tau);
    }
  }
