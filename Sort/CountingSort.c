/*
  计数排序用于一定范围内的整数，并且这些整数的值比较小。该算法通过统计每个整数在序列中出现的次数来实现排序。
  由于它不是通过比较实现排序的，所以nlgn并不是复杂度的下限。当然，计数排序经常作为基数排序的子程序，
  由此基数排序能够更有效的处理大的key值。它比桶排序相比，桶排序的每一个桶需要链表或者动态数组来存储数据。
*/

#define MAXCNT 10

void counting_sort(int arr[], int l, int r)
{
      int i, j, cnt[MAXCNT] = {0};
      int b[MAXCNT+MAXCNT] = {0};

      for (i = 0; i < MAXCNT; ++i)
            cnt[i] = 0;

      for (j = l; j <= r; ++j)
            cnt[arr[j] + 1]++;

      for (i = 1; i < MAXCNT; ++i)
            cnt[i] += cnt[i - 1];

      for (i = l; i <= r; ++i)
            b[cnt[arr[i]]++] = arr[i];

      for (j = l; j <= r; ++j)
            arr[i] = b[i-l];
}

/*
 上述code 的时间复杂度与空间复杂度均是O(n+k)，该算法的时间复杂度优化的空间不大，
 而空间复杂度可以进行优化，达到O(k)，它可以进行in-place排序达到。
举例说明
对于数列。arr[] = 3, 5, 1, 2, 1, 1, 2, 2, 3, 7, 5, 7
统计数组。cnt[] = 0, 3, 6, 8, 8, 10, 10, 12
以此来对arr进行in place 排序，arr[0]是3，而对应的cnt[3]是8，8-1=7即是3在arr所在位置的index，arr[7]的值是2，保存之。
arr[7]赋值3，同时cnt[3]减一。然后对于当前值2重复进行之前的操作，直到arr[0]等于最小的值。
当然对于arr中的每一个数据都进行这样的运算。最终，可以使arr整个数据有序。
*/

void inplace_counting_sort(int arr[], int l, int r)
{
      int i, j, tmp1 = 0, tmp2 = 0, cnt[MAXCNT] = {0};
      bool swap = false;

      for (i = 0; i < MAXCNT; ++i)
            cnt[i] = 0;

      for (j = l; j <= r; ++j)
            cnt[arr[j]]++;

      for (i = 1; i < MAXCNT; ++i)
            cnt[i] += cnt[i - 1];   

      tmp2 = arr[l];

      for (j = l; j <= r && cnt[arr[j]] > cnt[arr[j] - 1] && cnt[tmp2] != j; ++j)
      {
            tmp2 = arr[j];

            while (cnt[tmp2] - 1 != j ){        
                  tmp1 = arr[cnt[tmp2] - 1];
                  arr[cnt[tmp2] - 1] = tmp2;
                  cnt[tmp2]--;                  
                  tmp2 = tmp1;
            }

            arr[j] = tmp2;
            cnt[tmp2]--;
      }  
}

