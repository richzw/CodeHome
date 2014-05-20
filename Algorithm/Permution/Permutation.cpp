/*
  Permutation and combination for one string. such as "a b c"
*/

void permutation_recur(char arr[], int len, char* paux, string out)
{
    if (out.length() == len){
        cout << out << endl;
        return;
    }else {
        for (int index = 0; index < len; ++index){
            if (*(paux+index) == 1)
                    continue;
            *(paux+index) = 1;
            out.push_back(arr[index]);
            permutation_recur(arr, len, paux, out);

            *(paux+index) = 0;
            out.resize(out.length() - 1);
        }
    }
}

void permutation(char arr[], int len){
    char* paux = new char[len];
    if (paux == NULL)
        return;

    memset(paux, 0, len);
    string out;
    permutation_recur(arr, len, paux, out);

    delete[] paux;
}

void swap(char arr[], int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void output(char arr[], int len){
    for (int index = 0; index < len; ++index){
        cout << arr[index];
    }
    cout << endl;
}

void permutationBySwapRecur(char arr[], int cur, int len){
    if (cur == len){
        output(arr, len);
        return;
    } else {
        for (int index = cur; index < len; ++index){
            swap(arr, cur, index);
            permutationBySwapRecur(arr, cur+1, len);
            swap(arr, cur, index);
        }
     }
}

void permutationBySwap(char arr[], int len){
    if (arr == NULL || len <= 0)
            return;

    permutationBySwapRecur(arr, 0, len);
}
