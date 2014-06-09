/*
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm’s runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

//Do two binary searches, for max number equal or than target and target + 1

class Solution {
private:
    int searchMaxEqLess(int A[], int n, int target){
        int head = 0, tail = n - 1;
        while (head <= tail){
            if (head == tail){
                return A[head] < target ? head : head - 1;
            }
            if (head == tail - 1){
                return A[tail] < target ? tail : (A[head] < target ? head : head - 1);
            }
            int mid = head + (tail - head) / 2;
            if (A[mid] >= target){
                tail = mid - 1;
            } else {
                head = mid;
            }
        }
    }
public:
    vector<int> searchRange(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> out;
        if (n <= 0){
            return out;
        }
        int head = searchMaxEqLess(A, n, target);
        int tail = searchMaxEqLess(A, n, target + 1);
		if (head == tail){
		    head = tail = -1;
		} else {
		    head++;
		}
        out.push_back(head);
        out.push_back(tail);
 
        return out;
    }
};
