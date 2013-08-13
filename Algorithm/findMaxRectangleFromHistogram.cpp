/*
Q: 在柱状图中找最大的矩形：给一组非负的整数来表示一个柱状图，设计一个算法找到最大面积的能适合到柱状图内的矩形。
比如，对与这组数，1 2 3 4 1 ，有两种可能的方案，一种是适合到 2 3 4 内的矩形，面积是 2*3；
另一种是适合到 3 4 内的矩形，面积是 3*2。你觉得能有O(n)算法吗?
*/

/*
一个线性算法是用堆栈来保存当前可能的矩形（高度和起始位置）。从左到右扫描，对一个元素，如果 a）大于栈顶元素， push； 
b）小于的话，pop所有的大于它的元素，计算面积，更新最大值。
这时如果堆栈空，push一个新的元素，高度等于当前元素，起始位置为0；否则，push当前元素高度和栈顶的起始位置。
*/
#include <stack>

using namespace std;

typedef struct elem{
    unsigned char   index;
    unsigned int    val;
}elem;

int get_max_area(unsigned int arr[], int len)
{
    stack<elem> elem_stack;
    int max_val = 0;

    elem first;
    first.index = 0;
    first.val = arr[0];
    elem_stack.push(first);

    for (int i = 1; i < len; ++i)
    {
        if (elem_stack.size() > 0){
            elem el = elem_stack.top();
            if (arr[i] > el.val){
                elem e;
                e.index = i;
                e.val = arr[i];
                elem_stack.push(e);
            }else{
                int number = 1;
                while (elem_stack.top().val > arr[i]){
                    if (elem_stack.top().index * number > max_val){
                        max_val = elem_stack.top().index*number;
                    }
                    ++number;
                    elem_stack.pop();
                }
            }
        }else{
            elem new_elem;
            new_elem.index = i;
            new_elem.val = arr[i];

            elem_stack.push(new_elem);
        }
    }

    return max_val;
}

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

/*
扩展：在一个位图中找面积最大的白色矩形：给你一个NxN的黑白位图，找一个面积最大的全白色的矩形。
注意了，是一个矩形，不是任意一个白色相连的区域。你的算法能够达到的最好的时间复杂度是多少呢？
针对如下例子，有矩阵A：
110010
011111
111110
001100
*/

/*
生成新的矩阵C,C[i][j]表示第j列，从第i个元素开始，包括第i个元素，向上数，直到遇到0时，1的个数。则C为：
110010
021121
132230
003300
总结算法过程如下：
	* 初始(h,0)，入栈；
	* 遍历后续元素：
	* * 如果h > h_top, 则入栈；
	* * 如果h = h_top, 则不进行任何操作；
	* * 如果h < h_top, 出栈，直到栈顶元素的高度小于h，每次出栈，
	更新最大值(i - i_pop)*h_pop > max ? (i - i_pop)*h_pop : max；此时如果h>h_top,则push (h, i_lastpop)，
	如果栈为空，则push (h, 0).
	* 直到元素遍历完毕

*/
