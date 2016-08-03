/*
https://leetcode.com/articles/next-permutation/

把升序的排列（当然，也可以实现为降序）作为当前排列开始，然后依次计算当前排列的下一个字典序排列。
对当前排列从后向前扫描，找到一对为升序的相邻元素，记为i和j（i < j）。如果不存在这样一对为升序的相邻元素，则所有排列均已找到，
算法结束；否则，重新对当前排列从后向前扫描，找到第一个大于i的元素k，交换i和k，然后对从j开始到结束的子序列反转，
则此时得到的新排列就为下一个字典序排列。
*/

template <typename T> 
void CalcAllPermutation(T perm[],int num) 
{ 
   if (num < 1) 
        return; 
         
   while (true) { 
        int i; 
        for (i = num - 2; i >= 0; --i){ 
            if (perm[i] < perm[i + 1]) 
                break; 
        } 
         
        if (i < 0) 
            break;  // find all permutation
     
        int k; 
        for (k = num - 1; k > i; --k) { 
            if (perm[k] > perm[i]) 
                break; 
        } 
         
        swap(perm[i], perm[k]); 
        
        reverse(perm + i + 1, perm + num); 
   } 
} 
