/*
Q:城市的环形路有n个加油站，第i个加油站的油量用gas[i]来表示，你有如下的一辆车：
        1. 它的油缸是无限量的，初始是空的
        2. 它从第i个加油站到第i+1个加油站消耗油量为cost[i]
现在你可以从任意加油站开始，路过加油站可以不断的加油，问是否能够走完环形路。如果可以返回开始加油站的编号，
如果不可以返回-1。注意，解决方案保证是唯一的。

当我们从第0个加油站开始，判断是否可以走完，然后从第1个加油站开始，进行判断的时候，其实中间的计算已经做过了。
反过来，我们如果计算好了从第1个加油开始，到某一个站时，
油量为tank，此时考虑从第0个开始时，到该加油站的油量就是gas[i]-cost[i] + tank。
这时隐约觉得，解决方案的时间复杂度可以是O(n)的时间复杂度。
事实上确实可以，具体的方法如下：tank表示当前车的油缸里的油量
        1. 从第0个站开始，tank += gas[0] - cost[0]，只要tank>=0，我们就继续到下一个加油站
        2. 当不满足tank>=0，顺着环路试验从前一个站开始，比如，n-1: tank += gas[n-1] - cost[n-1]，如果还小于0，
        继续试验再前一个。
        3. 直到满足 tank>=0，再进行第1步，依次类推
        4. 当一前一后这两个相遇了，算法也就结束了，tank>=0，就成功，返回相遇的位置；否则，失败，返回-1
*/
int is_complete_road(int gas[], int cost[], int len){
	int tank = 0;
	int cur_index = 0, next_index = 1;
	bool forward_direction = true;
	bool bchanged = false;
	int steps = 1;

	while (cur_index != next_index){
		tank += gas[cur_index] - cost[cur_index];

		if (tank >= 0){
			if (forward_direction){
				if (cur_index + 1 < len)
					++cur_index;
				else
					cur_index = 0;
			} else {
				if (cur_index - 1 <= 0)
					--cur_index;
				else
					cur_index = len-1;
			}
			++steps;
		} else {
			if (!bchanged){
				if (forward_direction)
					next_index = cur_index - 1;
				else 
					next_index = cur_index + 1;
				bchanged = true;
			}
			if (forward_direction){
				if (cur_index - 2 >= 0)
					cur_index -= 2;
				else
					cur_index = len - 1;
			}else{
				if (cur_index + 2 < len)
					cur_index += 2;
				else
					cur_index = 0;
			}

			steps = 1;
			forward_direction = !forward_direction;
		}
	}

	return (tank >= 0 && steps == len)? 1:-1;
}
