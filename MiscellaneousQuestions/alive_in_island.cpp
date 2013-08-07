//一个小岛，表示为一个N×N的方格，从(0,0)到(N-1, N-1)，一个人站在岛上，位置(x, y)，他可以上下左右走，一步一个格子，
//他选择上下左右的可能性是一样的。当他走出小岛，就意味着死亡。假设他要走n步，请问他死亡的概率有多大？请写出求解代码。

/*
遇到这样的问题，就试着走几步好了。当一个人在(x,y)的时候，假设他此时，死亡的概率为p(x,y,n)，
然后，他有四种选择，而且是可能性相同，就是说，选择上下左右的概率都是1/4：
  * 选择上边，死亡的概率是多少呢？此时位置为(x, y-1)，剩余的步数为n-1,则概率为p(x, y - 1, n - 1)
	* 选择下边同理：概率为p(x, y + 1, n - 1)
	* 选择左边同理：概率为p(x - 1, y, n - 1)
	* 选择右边同理：概率为p(x + 1, y, n - 1)
则，p(x,y,n)=(p(x, y - 1, n - 1) + p(x, y + 1, n - 1) + p(x - 1, y, n - 1) + p(x + 1, y, n - 1))/4，可以表达出递归的形式。
*/

double probabilityOfAliveRecv(int x, int y, int n, int step, map<string, double>& map){
  if (step == 0)
		return 1.0;

	string key = "";
	key.append(to_string(static_cast<long long>(x))+",");
	key.append(to_string(static_cast<long long>(y))+",");
	key.append(to_string(static_cast<long long>(step)));

	if (map.find(key) != map.end())
		return map[key];

	double prob = 0.0;
	if (x > 0)
		prob += (probabilityOfAliveRecv(x-1, y, n, n-1, map))/4;
	if (x < n-1)
		prob += (probabilityOfAliveRecv(x+1, y, n, n-1, map))/4;
	if (y > 0)
		prob += (probabilityOfAliveRecv(x, y-1, n, n-1, map))/4;
	if (y < n-1)
		prob += (probabilityOfAliveRecv(x, y+1, n, n-1, map))/4;
	map.insert(pair<string, double>(key, prob));
	
	return prob;
}
double probabilityOfAlive(int x, int y, int n){
	if (x < 0 || x > (n-1) || y < 0 || y > (n-1) || n < 1) 
		return 0.0;

	map<string, double>	prob_map;
	return probabilityOfAliveRecv(x, y, n, n, prob_map);
}
