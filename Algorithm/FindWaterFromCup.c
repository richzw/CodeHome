/*
有一座金字塔，从上到下，第一层有一个杯子、第二层有两个杯子，依次类推。对杯子进行编号，有如下的形状：
   1
 2   3
4   5   6
每个杯子的容量为C升，从塔顶倒下L升水，当1号杯子满了之后，会等量溢出到2号和3号杯子。
当2号和3号满了，2号溢出到4号和5号，3号溢出到5号和6号，注意5号接受来自两个杯子的水。依次类推。
给定C和L，请问，第n杯里有多少水。

这个类型的题目，关键点就是明了水倒下来的过程。我们这里做简单的分析， 假设L>C, 如果L
金字塔深度0 1 1 2 2 2
杯号      1 2 3 4 5 6
A索引     0 1 2 3 4 5
观察上面的表格，我们会发现，一个规律，i号杯深度为h，则i号中溢出的水，将平分进入：
        * i + h + 1
        * i + h + 2
比如，文章开始的图中，3号杯进入5号和六号，3号杯的h为1，则
        * 5 = 3 + 1 + 1
        * 6 = 3 + 1 + 2
利用这个技巧，可以在数组中存储树形的金字塔，并且可以很方便的找到孩子节点。
计算出所有的A[i]之后，要得到最后的答案，还有一部之遥。即：
        * A[i] >= C ? C : A[i]
*/
int get_water_cup_of(int capacity, int totle_water, int cup_number){
	assert(cup_number >= 0 && cup_number < 6);
	int cup_arr[6] = {0};
	int cup_dep[6] = {0, 1, 1, 2, 2, 2};
	int i = 0;

	while (i < 6 && totle_water > 0){
		if (totle_water >= capacity*(cup_dep[i]+1)){
			int cup_cnt = cup_dep[i] + 1;
			for (int j = 0; j < cup_cnt; ++j){
				cup_arr[i] = capacity;
				++i;
				totle_water -= capacity;
			}
		}else{
			int cup_cnt = cup_dep[i];
			int each_cap = totle_water/cup_cnt;
			for (int j = 0; j < cup_cnt; ++j){
				cup_arr[i-j-1 +cup_dep[i-1]+1] += each_cap/2;
				cup_arr[i-j-1 +cup_dep[i-1]+2] += each_cap/2;
			}
			totle_water = 0;

			for (; i < 6; ++i){
				cup_arr[i] = (cup_arr[i] >= capacity)? capacity: cup_arr[i];
			}
		}
	}

	return cup_arr[cup_number];
}
