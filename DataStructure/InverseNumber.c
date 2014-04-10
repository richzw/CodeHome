// merge sort implementation for inverse number
__int64 change;  
int arr[505000];  
  
void merge(int arr[], int leftPos, int rightPos, int rightEnd) //合并 
{  
    int *temp = (int*)malloc((rightEnd-leftPos+3)*sizeof(int));  
    int leftEnd = rightPos - 1;  
    int tempPos = 0;  
    int start = leftPos;  
    while(leftPos <= leftEnd && rightPos <= rightEnd)  
    {  
        if(arr[leftPos] <= arr[rightPos])  
        {  
            temp[tempPos++] = arr[leftPos++];  
        }  
        else  
        {  
            temp[tempPos++] = arr[rightPos++];  
            change += leftEnd - leftPos + 1; //
        }  
    }  
    while(leftPos <= leftEnd)  
    {  
        temp[tempPos++] = arr[leftPos++];  
    }  
    while(rightPos <= rightEnd)  
    {  
        temp[tempPos++] = arr[rightPos++];  
    }  
    for(int i=0; i<tempPos; i++)  
    {  
        arr[start+i] = temp[i];  
    }  
    free(temp);  
}  
void mergeSort(int arr[], int left, int right) // 
{  
    if(left < right)  
    {  
        int center = (left + right) / 2;  
        mergeSort(arr,left,center);  
        mergeSort(arr,center+1,right);  
        merge(arr,left,center+1,right);  
    }  
}  
int main()  
{  
    int n;  
    while(cin>>n,n)  
    {  
        change = 0;  
        for(int i=0; i<n; i++)  
        {  
            cin>>arr[i];  
        }  
        mergeSort(arr,0,n-1);  
        cout<<change<<endl;  
    }  
    return 0;  
}
