//Q: 整数集合s和一个整数sum，求集合s的所有子集su,使得su的元素之和为sum
  
 #include <iostream>
 using namespace std;

 int sum = 10;
 int subsum = 0;
 int s[5]= {1, 3, 6, 4, 2};
 int x[5]={0};
 int N = 5;

 void print(){
     for (int index = 0; index < N; ++index)
         if (x[index] == 1)
             cout << s[index] << " ";
     cout << endl;
 }

 void sumSet(int index){
     if (index >= N){
         if (sum == subsum)
             print();
         return;
     }
     if (subsum < sum){
         x[index] = 1;
         subsum += s[index];
         sumSet(index + 1);
         subsum -= s[index];
     }
     x[index] = 0;
     sumSet(index + 1);
 }

 int main(){
     sumSet(0);
 
     return 0;
 }
