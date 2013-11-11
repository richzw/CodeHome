/*
给定一组区间，表示为[start, end]，请给出方法，将有重叠的区间进行合并。​
例如：给定：[1,3],[2,6],[8,10],[15,18]，合并：[1,6],[8,10],[15,18].​

​
分析：题目很直观，首先把区间递增排序，然后从头合并，合并时观察当前区间的start是否小于或等于前一个区间的end。

*/

class Interval{
public:
	Interval(int start, int end):m_start(start), m_end(end){}

public:
	int m_start;
	int m_end;
};

int cmp(const Interval& v1, const Interval& v2){
	if (v1.m_start < v2.m_start)
		return true;
	else if (v1.m_start == v2.m_start && v1.m_end < v2.m_end)
		return true;
	return false;
}

vector<Interval> merge(vector<Interval>& intervals){
	if (intervals.size() <= 1)
		return intervals;

	sort(intervals.begin(), intervals.end(), cmp);
	vector<Interval> vec;
	int start = intervals[0].m_start, end = intervals[0].m_end;
	for (int i = 1; i < intervals.size(); ++i){
		if (intervals[i].m_start <= end){
			end = max(end, intervals[i].m_end);
		}else{
			Interval tmp(start, end);
			vec.push_back(tmp);
			start = intervals[i].m_start;
			end = intervals[i].m_end;
		}
	}
	Interval tmp(start, end);
	vec.push_back(tmp);

	return vec;
}
