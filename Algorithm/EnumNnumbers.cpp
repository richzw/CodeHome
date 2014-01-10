/*
给定数字n，请给出方法，打印出所有的位数是n的数字，并且每一个数字，每一位从左到右依次变大。​
例如：n=3时(123,124,125...789).
*/
void print_num_recv(string s, int c, int len){
	if (s.length() == len){
		cout << s << " ";
		return;
	}

	for (int num = c+1; num < 10; ++num){
		if (s.length() + 1 == len){
			cout << s+to_string((long long)num) << " ";
			//s.pop_back();
		}else{
			print_num_recv(s+to_string((long long)num), num, len); 
		}
	}
}

void print_num(int n){
	if (n < 1 || n > 9)
		return;

	for (int num = 1; num <= 10-n /*key*/; ++num){
		print_num_recv(to_string((long long)num)+"", num, n);
	}
}
