//

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

void print(char arr[], int len, char* paux){
    for (int index = 0; index < len; ++index){
        if (*(paux+index) == 1)
            cout << arr[index];
    }
    cout << endl;
}

void combine_recur(char arr[], int cur, int len, char* paux){
    if (cur >= len)
        print(arr, len, paux);
    else{
        *(paux+cur) = 1;
        combine_recur(arr, cur+1, len, paux);
        *(paux+cur) = 0;
        combine_recur(arr, cur+1, len, paux);
    }
}

void combine(char arr[], int len){
    if (arr == NULL || len <= 0)
        return;
    char* paux = new char[len];
    if (paux == NULL)
        return;

    memset(paux, 0, len);
    combine_recur(arr, 0, len, paux);

    delete[] paux;
}


