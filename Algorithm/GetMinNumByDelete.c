/*
对于一个n位正整数a,去掉其中任意k(k<=n)个数字后，剩下的数字按原次序排列可以组成一个新的正整数。设计一个删除算法，使得剩下的数字组成的正整数最小。
例如，a=13243221，k=5，输出：121
分析
遇到这个题目，我们可以首先把问题简单化，考虑k=1的情况，在上面的例子中，直观上应该删去3，得到1243221，继续考虑k=1的情况，应该继续删去4，得到123221。
我们之前删去的3和4共同具有的特点：都是第一个递减序列的首个数字。再考虑如果数字串中没有递减序列，
如a=123，k=1的情况，应该删掉最后一个字符3，得到最小正整数12。
因此，这个题目我们只需要不断的删除首个递减序列的首个数字，如果没有递减序列则删去最后一个字符。
时间复杂度o(n*k)​

继续思考，发现我们循环从头删除重复做了很多无用功。如果第i个字符比第i+1个字符大，则删掉第i个字符，此时，前i-1个字符是递增序列，
因此我们可以比较第i+1个字符及第i-1个字符，如果第i+1个字符大于第i-1，则从i+1个字符开始继续往前寻找递减序列的首个字符，
如果第i-1个字符大于第i+1个字符，则应删除第i-1个字符。时间复杂度为o(n+k)
*/
string delete_number(string str, int k){
	int len = str.length();

	while (k-- > 0){	
		char pre = str[1];
		char pos = str[0];
		int i;

		for (i = 2; i < len - 1; ++i){
			if (pre < pos){
				str.erase(i-2, 1);
				break;
			}			
			
			pos = pre;
			pre = str[i];
		}

		// erase the last char, in case of the ascending order
		if (i == len - 1){
			str.pop_back();
		}
	}

	return str;
}

string deleteNum(string input, int k){
	int k_orig = k;
	int len = input.size();

	while (k){
		int i = 0;
		for (; i < len - 1; ++i){
			if (input[i] > input [i+1])
				break;
		}

		for (; i < len - 1; ++i)
			input[i] = input[i+1];

		--k;
		--len;
	}

	return input.substr(0, input.size() - k_orig);
}

string delete_number_v1(string str, int k){
	int len = str.length();
	int index = 0;
	char pos = str[index];
	++index;
	char pre = str[index];

	while (k > 0 ){
		if (pre < pos){
			str.erase(index-1, 1);
			--k;
			if (index < str.length())
				pre = str[index];
			if (index-1 > 0)
				pos = str[index - 1];
		}else{
			pos = pre;
			++index;
			pre = str[index];
		}
	}

	return str;
}
