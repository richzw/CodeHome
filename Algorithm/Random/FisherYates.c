void ShuffleArray_Fisher_Yates(char* arr, int len)
{
    int i = len, j;
    char temp;
 
    if ( i == 0 ) return;
    while ( --i ) {
        j = rand() % (i+1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

