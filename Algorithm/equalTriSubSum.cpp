    1 #include <iostream>
    2 #include <unordered_map>
    3 
    4 using namespace std;
    5 
    6 bool IsEqualTripuleSubSum(int arr[], int len) {
    7     if (arr == NULL || len == 0)
    8         return false;
    9 
>> 10     int* subSum = new int[len];
   11     if (subSum == NULL)
   12         return false;
   13 
   14     unordered_map<int, int> hmap;
   15     subSum[0] = arr[0];
   16     hmap.insert(make_pair<int, int>(arr[0], 0));
   17     for (int idx = 1; idx < len; ++idx) {
   18         subSum[idx] = subSum[idx-1] + arr[idx];
>> 19         hmap.insert(make_pair<int, int>(sunSum[idx], idx));
   20     }
   21 
   22     int curSum = 0;
   23     unordered_map<int, int>::const_iterator itor;
   24     for (int idx = len-1; idx > 0; --idx) {
   25         curSum += subSum[idx];
   26         itor = hmap.find(curSum);
   27         if (itor != hmap.end()){
   28             if (subSum[idx] - subSum[itor->second] == curSum)
   29                 return true;                                                                                                                                                   
   30         }
   31     }
   32 
   33     return false;
   34 }
   35 
   36 int main() {
   37     int arr[] = {-1, 3, 2, 1, 1, -2, 2};
   38 
   39 
   40 }
