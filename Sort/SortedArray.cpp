/*
  Q: An array with n elements which is K most sorted, namely the distance between the current index and sorted index
     is less than K. It should be faster than O(n*lgn)
*/

// Solution: build an Kth min heap, time k*lgk + (n-k)lgk

#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

void shiftdown(int arr[], int root, int right){
    int child = 2*root + 1;

    if (child < right && (child + 1) < right){
            child = (arr[child] < arr[child + 1])? (child + 1): child;
    } else {
        return;
    }

    if (arr[root] > arr[child])
        return;

    swap(arr[root], arr[child]);

    shiftdown(arr, child, right);
}

void hSort(int arr[], int size){
    for (int index = size/2; index >= 0; --index){
        shiftdown(arr, index, size);
    }

    for (int index = size; index > 0; --index){
        swap(arr[0], arr[index]);
        shiftdown(arr, 0, index);
    }
}

int main(){
    int interval = 5;
    int array[] = {3, 2, 1, 6, 4, 7, 5, 9, 10, 8};
    copy(array,
         array + sizeof(array)/sizeof(array[0]),
         ostream_iterator<int>(cout, " "));
    cout << endl;

    hSort(array, interval);
    for (int index = 0; index < (sizeof(array)/sizeof(array[0]) - interval); ++interval){
        hSort(array + index, interval);
    }

    copy(array,
         array + sizeof(array)/sizeof(array[0]),
         ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
