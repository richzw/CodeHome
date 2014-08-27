//
//Q: intersection of sorted lists; 给定几个sorted lists，写程序求它们的交集

// basic approach
vector<int> intersectionList(vector<vector<int> > vectors){
	int vec_num = vectors.size();

	vector<int> vec_pos(vec_num);// hold the current position for every array
	vector<int> inter_vec; // collection of intersection elements
	
	while (true){
		int max_val = INT_MIN;
		for (int index = 0; index < vec_num; ++index){		
			if (vec_pos[index] == vectors[index].size()){
				return inter_vec;
			}

			max_val = max(max_val, vectors[index].at(vec_pos[index]));
		}

		bool bsame = true;
		for (int index = 0; index < vec_num; ++index){
			while (vectors[index].at(vec_pos[index]) < max_val){
				vec_pos[index]++;
				bsame = false;
			}
		}

		if (bsame){
			inter_vec.push_back(vectors[0].at(vec_pos[0]));

			for (int index = 0; index < vec_num; ++index){
				vec_pos[index]++;
			}
		}
	}

}

template<class Output, class... Cs>
Output intersect( Output out, Cs const&... cs ) {
  using std::begin; using std::end;
  auto its = std::make_tuple( begin(cs)... );
  const auto ends = std::make_tuple( end(cs)... );
  while( !at_end( its, ends ) ) {
    if ( all_same( its ) ) {
      *out++ = *std::get<0>(its);
      advance_all( its );
    } else {
      advance_least( its );
    }
  }
  return out;
}

//参考答案。另外一种是用最小堆，堆中存放第几个list和list中的位置，同时一个变量存放当前最大值。
//每次移动堆中最小list中元素，和之前最大值比较。相等则有共同元素。循环至结束。
