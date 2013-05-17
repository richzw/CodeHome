/*
Q: 一个机器人一天能够找到4个金币，而50个金币可以购买新的机器人，问：在第N天，能够找到的金币数量的最大值？
*/

/*
简单分析可得，如果有足够的钱，越早换机器人，对于不久后的某一天找到的金币数量越多。
于是，依据动态规划的方法，构造一个换机器人的天数以及剩余金币的列表。
然后，遍历这个列表找到金币最多的机器人数。结果可得。
*/

struct data{
  int remain;  //the remain coin after transfer to one robot
	int tday;    //the day that have 50 coin and transfer to one more robot
};

int findMaxCoin(int endDay){
	int robot_count = 1;
	int day_coin = 4;
	int robot_coin = 50;
	int max_coin = 0;
	vector<data>  vec; // the index of vec means the number of robots (1 base)
	data elem;

	elem.remain = 0;
	elem.tday = 0;
	vec.push_back(elem); //dummy element

        //compute the first element
	elem.tday = (robot_coin%day_coin == 0)?(robot_coin/day_coin):(robot_coin/day_coin + 1);
	elem.remain = elem.tday * day_coin - robot_coin;
	vec.push_back(elem);
	robot_count++;
        
        //construct the vec. once there is enough money to buy one robot and do it.
	for (int day = elem.tday; day < endDay; ++day){
		if ((day - vec[robot_count-1].tday)*day_coin*robot_count + vec[robot_count-1].remain >= robot_coin){
			elem.tday = day;
			elem.remain = vec[robot_count-1].remain + robot_count * day_coin * (day - vec[robot_count-1].tday) - robot_coin;
			vec.push_back(elem);
			robot_count++;
		}
	}
	
        //find the max coins from index vec  
	for (vector<data>::size_type index = 0; index < vec.size(); ++index){
		int coin = vec[index].remain + day_coin*(index + 1)*(endDay - vec[index].tday);
		if (coin > max_coin)
			max_coin = coin;
	}

	return max_coin;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "day 26 is " << findMaxCoin(26) << endl;
	cout << "day 13 is " << findMaxCoin(13) << endl;
	cout << "day 35 is " << findMaxCoin(35) << endl;

	return 0;
}

/*
Fix me：达到某一数量之后，一天可以买多台机器人偶。。。
*/
struct data{
    int remain;
    int tday;
    int rnum;
};

int findMaxCoin(int endDay ){
    int robot_count = 1;
    int day_coin = 4;
    int robot_coin = 50;
    int max_coin = 0;
    vector<data> vec;
    data elem;

    elem.remain = 0;
    elem.tday = 0;
    elem.rnum = 1;
    vec.push_back(elem);

    robot_count++;
    elem.tday = (robot_coin%day_coin == 0)?(robot_coin/day_coin):(robot_coin/day_coin + 1);
    elem.remain = elem.tday * day_coin - robot_coin;
    elem.rnum = robot_count;
    vec.push_back(elem);

    int coin_num = 0;
    int robot_inc = 0;
    for (int day = elem.tday; day < endDay; ++day){
        coin_num = (day - elem.tday)*day_coin*robot_count + elem.remain;
        if (coin_num >= robot_coin){
            elem.tday = day;
            robot_inc = coin_num/robot_coin;
            elem.remain = coin_num%robot_coin;
            robot_count += robot_inc;
            elem.rnum = robot_count;
            vec.push_back(elem);
        }
    }

    for (vector<data>::size_type index = 0; index < vec.size(); ++index){
        int coin = vec[index].remain + day_coin*(vec[index].rnum)*(endDay - vec[index].tday);
        if (coin > max_coin)
            max_coin = coin;
    }

    return max_coin;
}

