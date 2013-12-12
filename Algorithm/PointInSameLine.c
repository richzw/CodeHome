/*
平面上有n个点，某些点会出现在同一条直线上，请给出方法找到在同一条直线上点最多的情况，给出数目即可。
​
一条直线，有两个决定因素：​  1. 斜率​    2. 截距
那么，在平面上通过同一个点并且斜率相同的直线一定是重合的，否则就与截距的条件矛盾。
并且两点决定一条直线，我们可以算出这点和其他所有点的斜率，找到出现最多的斜率，那么我们就得到了通过这点的直线中穿过的点数最多的一条直线及其点数；
然后我们对每一个点都找到这样的一条直线及其通过的点数；最后取整体最大的一个点数值即为我们所求。
在这个过程中需要注意两点：
1、对于位于同一竖线的点，斜率为无穷大，需要进行处理
2、对于重复的点也需要进行处理
*/
class Point{
public:
	int x;
	int y;
};

int get_max_pointers(vector<Point> pointvec){
	if (pointvec.size() == 0)
		return 0;

	int imax = 0;
	int vertical_line = 0;
	unordered_map<float, int> map;
	for (int i = 0; i < pointvec.size(); ++i){
		int same = 0;
		
		for (int j = 0; j < pointvec.size(); ++j){
			if (pointvec[i].x == pointvec[j].x && pointvec[j].y == pointvec[j].y){
				++same;
			}else if (pointvec[i].x == pointvec[j].x && pointvec[j].y != pointvec[j].y){
				++vertical_line = 0;
			}else{
				float slope = (float)(pointvec[j].y - pointvec[j].y)/(float)(pointvec[i].x - pointvec[j].x);
				map[slope]++;

				if (map[slope] > imax){
					imax = map[slope];
				}
			}

			if (imax < vertical_line){
				imax = vertical_line;
			}
		} 
	}

	return imax;
}
