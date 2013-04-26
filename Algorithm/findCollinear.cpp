/*
* @func: solve http://coursera.cs.princeton.edu/algs4/assignments/collinear.html
*/
typedef struct point{
  double x;
	double y;
}point;

typedef vector<point> pointvector;
//TODO: replace multimap with unordered_multimap...
typedef multimap<double/*point slope*/, int/*point index of point vector*/> pointslopmap;

double pointslope(point source, point dest){
	return (dest.y - source.y)/(dest.x - source.x);
}

#define MAXLEN  50 /* the max number of point can be handled */

/*
* @func: 
* @params: vec{point}, the point arrays.
*          len{len}, the length of the vec.
* @ret: vecRet{point}, the points arrays those points are collinear.
* @ret: lenRet{int}, 
*/
void solve(point vec[], int len, point vecRet[], int& lenRet){//(pointvector vec){
	pair<multimap<double, int>::iterator, multimap<double, int>::iterator> point_itors;
	pointslopmap point_slop_map;
	int point_number = len;//vec.size();
	double slope = 0;
	lenRet = 0;

	// can not handle the length of vec is more than MAXLEN
	if (len > MAXLEN)
		return;

	for (int i = 0; i <  point_number; ++i){
		point point_source = vec[i];
		for (int j = 0; j < point_number; ++j){
			if (j == i)
				continue;

			point point_dest = vec[j];
			slope = pointslope(point_source, point_dest);
			
			//prevent inserting same node into multimap
			bool bsame_point = false;
			multimap<double, int>::iterator itor;
			for (itor = point_slop_map.lower_bound(slope); 
				itor != point_slop_map.upper_bound(slope) && itor->first == slope; 
				++itor)
			{
				if (itor->second == j){
					bsame_point = true;
					break;
				}
			}
	
			if (!bsame_point){
				//save the pointer and slope into multimap -- RB tree, O(logN)
				point_slop_map.insert(pair<double, int>(slope, j));
			}
		}
	}

	//tranverse the map to find the pointers collinear
	int number = 1;

	pointslopmap::iterator itor = point_slop_map.begin();
	double slope_pre = itor->first;
	++itor;
	while (itor != point_slop_map.end()){
		double slope_cur = itor->first;
		if (slope_cur == slope_pre){
			++number;
		}else {
			if (number >= 3){
				point_itors = point_slop_map.equal_range(slope_pre);
				//output the collinear pointers
				for (multimap<double, int>::iterator it = point_itors.first; it != point_itors.second; ++it){
					cout << "(" << vec[it->second].x << " " << vec[it->second].y << ")" << " -> ";
					vecRet[lenRet].x = vec[it->second].x;
					vecRet[lenRet].y = vec[it->second].y;
					++lenRet;
				}
				cout << endl;
			}
			number = 1;
		}
		slope_pre = slope_cur;
		++itor;
	}
}
