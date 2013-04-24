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

void combine_string_recur(char arr[], int cur, int len, string out){
  if (out.length() > 0 && out.length() <= len)
		cout << out << endl;
	for (int index = cur; index < len; ++index){
		out.push_back(arr[index]);
		combine_string_recur(arr, index+1, len, out);
		out.resize(out.length() - 1);
	}
}

void combine_string(char arr[], int len){
	if (arr == NULL || len <= 0)
		return;
	string out;
	combine_string_recur(arr, 0, len, out);
}



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
