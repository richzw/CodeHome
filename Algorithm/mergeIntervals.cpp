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
/*
一个很巧妙的做法就是进入一个区间就加1，出一个区间就减1，如果数值大于0，说明当前处于一个区间中。

设数组 int l[30], r[30]，初始化全部为0 
[1, 4]：l[1]++, r[4]--
[8, 9]：l[8]++, r[9]--
...

扫描时，用一个count记录，每次：
count += l[i]，如果count>0说明i处于一个区间中
count -= r[i]，如果count==0说明i是一个区间的尾端点
*/
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<Interval> answer;
        if (intervals.empty()) {
            return answer;
        }

        int min = 1000000, max = -1000000;
        for (vector<Interval>::iterator iter = intervals.begin(); iter != intervals.end(); iter++) {
            min = min < iter->start ? min : iter->start;
            max = max > iter->end ? max : iter->end;
        }
        
        int left[max - min + 1];
        int right[max - min + 1];
        memset(left, 0, sizeof(int) * (max - min + 1));
        memset(right, 0, sizeof(int) * (max - min + 1));
        for (vector<Interval>::iterator iter = intervals.begin(); iter != intervals.end(); iter++) {
            left[iter->start - min]++;
            right[iter->end - min]++;
        }
        
        int start = -1, count = 0;
        for (int i = 0; i < max - min + 1; i++) {
            count += left[i];
            if (count > 0 && start == -1) {
                start = i;
            }
            count -= right[i];
            if (count == 0 && start != -1) {
                answer.push_back(Interval(start + min, i + min));
                start = -1;
            }
        }
        
        return answer;
    }
};

/*
同样给定一组区间，将区间中存在的任意区间的区间删除。​
例如：给定：[1,2] ,[1,3],[1,4],[5,9],[6,8]，删除后：[1,2],[6,8].​
​
我们可以按照start递增排序，若start相等，则按照end递减排序。考虑排序后的第i-1 和第i个区间，
由于start是递增的，所以第i-1个区间的start肯定小于等于第i个区间的start。
若第i-1个区间的end大于等于第i个区间的end，则第i-1个区间就成为第i个区间的父区间了。​
按照这个思路，可以试着在排序之后逆向顺序处理每一个区间。假设当前处理第i个区间，
如前所述，若第i-1个区间的end大于等于第i个区间的end，则第i-1个区间成为第i个区间的父区间，
可以保留第i个区间，将第i-1个区间删除。由于第i-1个区间是第i个区间的父区间，
所以第i-1个区间的父区间也是第i个区间的父区间，这种情形下删掉第i-1个区间，后续不会漏删第i-1个区间的父区间。​
若第i-1个区间的end小于第i个区间的end，则可以跳过第i个区间，开始处理第i-1个区间。
因为按照这种处理的方法，在处理到第i个区间时，该区间不会是任何区间的父区间（若是父区间已经被如前所述的方法删除了）。
而且，在这种情形下，后续可能出现的第i个区间的父区间会是第i-1个区间的父区间，所以也不会漏掉第i个区间的父区间。
所以排序之后逆向处理，只需要O(N)的时间，就可以解决这道问题。整体的时间复杂度为O(nlogn)。
*/
int inter_cmp(const Interval& v1, const Interval& v2){
	if (v1.m_start < v2.m_start)
		return true;
	else if (v1.m_start == v2.m_start && v1.m_end > v2.m_end)
		return true;
	return false;
}

vector<Interval> delete_interval(vector<Interval> intervals){
	if (intervals.size() <= 1)
		return intervals;

	sort(intervals.begin(), intervals.end(), inter_cmp);

	vector<Interval>::reverse_iterator  cur_iter = intervals.rbegin();
	vector<Interval>::reverse_iterator  pre_iter = cur_iter + 1;
	int cur_end = cur_iter->m_end;
	int cur_start = cur_iter->m_start;

	while ( pre_iter != intervals.rend()){
		//erase the previous node
		if (pre_iter->m_end > cur_end/*pre_iter->m_end > cur_iter->m_end*/){
			++pre_iter;
			pre_iter = reverse_iterator<vector<Interval>::iterator>(intervals.erase(pre_iter.base()));
			// after the erase is invoked, the current iterator is invalid!!!
			cur_iter = pre_iter;
			continue;
		} // erase the current node
		else if (pre_iter->m_end > cur_end && pre_iter->m_start == cur_start){
			++pre_iter;
			cur_iter = reverse_iterator<vector<Interval>::iterator>(intervals.erase(cur_iter.base()));
			continue;
		}
		++pre_iter;
		cur_end = cur_iter->m_end;
		cur_start = cur_iter->m_start;
	}

	return intervals;
}
