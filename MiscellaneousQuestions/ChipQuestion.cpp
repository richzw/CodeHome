/*
  Q: 有足够量的2分、5分、1分硬币，请问凑齐1元钱有多少种方法？
*/

// Solution: 
//我们从简单情况开始分析，假如有足够量的1分硬币，请问凑齐1分钱有多少种方法？毫无疑问，答案是1。
//然后，凑齐2分钱有多少种方法？凑齐n分钱有多少种方法？答案均是1。
//接下来，假如有足够量的1分硬币和2分硬币，凑齐n分钱有多少种方法？对于1分硬币，凑齐任意n分钱都只有1种方法；
//那么只用1分钱凑齐n-2分钱，有1种方法；只用1分钱凑齐n-4分钱，有1种方法；只用1分钱凑齐n-6分钱，也有1种方法......

//由此，用a1～ak种硬币，凑齐n分钱，记做S(k,n)。 可以得到递归公式S(k,n)=∑_S(k-1,n-m*ak)  m=0~n/ak。
//

#include <iostream>  
#include <vector>  
using namespace std;  
 
int maxcombine(vector<int> vec, int amount){  
    int coin = 0;  
    int coin_number = 1;  
    int number = 0;  
 
    if (vec.size() > 1){  
        coin = vec.back();  
        vec.pop_back();  
    } else {  
        ++number;  
        return number;  
    }  
 
    while(coin * coin_number < amount){  
        number += maxcombine(vec, amount - coin_number*coin);  
        ++coin_number;  
    }  
 
    return number;  
}  
 
int main(){  
    vector<int> vec;  
    int amount = 100;  
    int num = 0;  
    vec.push_back(1); // 1 is the first element of vector intentionally.   
    vec.push_back(2);  
    vec.push_back(5);  
 
    num = maxcombine(vec, amount);  
    cout << "the amount 100 combination count is " << num << endl;  
 
    return 0;  
}  

