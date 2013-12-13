/*
Q: 给定软件的版本号的表示方式，以及一些版本号，请找出最新的版本。例如：
        1. 1.2，2.2 最新的是2.2
        2. 3.1, 3.1.3 最新的是3.1.3
上面的版本号，都是用字符串表示的。

比较的方式就是我们自定义的比较操作符，一个方法，在比较的时候，可以将字符串进行按“.”划分，对应的部分比较数字的大小。
假设有n个版本号，每个版本号的长度为k，则整体的时间复杂度为O(knlogn)，其中，划分并且逐位比较的时间复杂度为O(k)。
是否有更加高效的方法呢？因为我们要找的最新的版本（可以理解为最大的），一般来讲，我们给定一个数组，找到最大的元素
，O(n)的时间复杂度就可以的。同样，在这里我们仍旧可以这样处理：
        1. 用对每一个版本号进行划分，保存为正数的list
        2. 遍历每一个list的第一个元素，找到的最大的数字，也许会有多个
        3. 对于第一个数字最大的一些版本，处理第二个数字，同样找到最大的数字，缩小进一步查找的范围
        4. 依次类推。
这个方法的时间复杂度为O(kn)。
*/
string get_max_version(vector<string> strVec){
	if (strVec.size() == 0)
		return string("");

	vector<string> max_group;
	int len = strVec.size();

	// put the first element into vector
	max_group.push_back(strVec[0]);
	for (int idx = 1 ; idx < len; ++idx){
		// if find the larger number, clear the old number group and add the large number
		if (max_group[0].at(0) < strVec[idx].at(0)){
			max_group.clear();
			max_group.push_back(strVec[idx]);
		}else if (max_group[0].at(0) == strVec[idx].at(0)){
			max_group.push_back(strVec[idx]);
		}
	}

	int idx = 2;
	string max_str = "";
	while (true){
		bool bcompare = false;
		max_str = max_group[0];
		for (int group_idx = 1; group_idx < max_group.size(); ++group_idx){
			if (max_group[group_idx].size() > max_str.size()){
				max_str = max_group[group_idx];
				continue;
			}
			cout << "idx is " << idx << endl;
			if (idx < max_group[group_idx].size() 
				&& max_group[group_idx].at(idx) >= max_str.at(idx)){
				max_str = max_group[group_idx];
				bcompare = true;
			}
		}
		// if there is no number to be compared, just exit
		if (!bcompare)
			break;

		idx += 2;
	}

	return max_str;
}
