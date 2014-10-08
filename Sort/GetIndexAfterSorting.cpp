/*
比如数组a,a[0]=2,a[1]=1,a[2]=5,a[3]=4,要按照数值对数组进行排序，排序后的结果即为5,4,2,1，但我需要的是它们的索引，即2,3,0,1
*/

	const int elem_size = 4;
	int elements[elem_size] = {2, 1, 5, 3};
	bool elem_compare(int a, int b){
		return elements[a] > elements[b];
	}

	int ranks[elem_size];
	for (int i = 0; i < elem_size; ++i) { 
     ranks[i] = i; 
   } 
   std::sort(ranks, ranks + elem_size, elem_compare); 
   
