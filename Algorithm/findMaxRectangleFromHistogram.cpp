/*
Q: 在柱状图中找最大的矩形：给一组非负的整数来表示一个柱状图，设计一个算法找到最大面积的能适合到柱状图内的矩形。
比如，对与这组数，1 2 3 4 1 ，有两种可能的方案，一种是适合到 2 3 4 内的矩形，面积是 2*3；
另一种是适合到 3 4 内的矩形，面积是 3*2。你觉得能有O(n)算法吗?

*/

/*
设柱状图为非负整数数组A, 则最大矩形的高度必定是数组的某一项A[i]。顾设f(i) 为以数组第i项的高度为矩形高度时矩形的最大宽度，
则最大矩形为max{f(i)*A[i]}, i = 0...len-1f(i)本身无法动态规划，但若将f(i)拆成左右两部分，则很容易动态规划求解
令left(i)为以数组第i项为矩形高度时矩形左侧最大宽度，right(i)为以数组第i项为矩形高度时矩形右侧的最大宽度，
则f(i) = left(i) + right(i) - 1
*/

int maxRectangle(int A[], int len)
{
     assert(len >= 0 && all_of(A, A+len, [](int v){return v >= 0;}) );
     if(len  == 0){
           return  0;
     }
     vector<int>  left(len), right(len);
     for(int i = 0; i < len; i++){
         left[i] = 1;
         for(int j = i - 1; j >= 0 && A[j] >= A[i]; ){
             left[i] += left[j];
             j -= left[j];
         }
     }
     for(int i = len-1; i >= 0; i--){
          right[i] = 1;
          for(int j = i+1; j < len && A[j] >= A[i]; ){
             right[i] += right[j];
             j += right[j];
          }
     }
     int maxR = 0;
     for(int i = 0; i < len; i++){
         int r = (left[i] + right[i] - 1) * A[i];
         if(r > maxR){
              maxR = r;
         }
      }
      return  maxR;
}

