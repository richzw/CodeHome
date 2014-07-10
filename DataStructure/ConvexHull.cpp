class Point{
private:
	double x;
	double y;

public:
	Point(double x, double y): x(x), y(y){}
	~Point() {}

	void SetX(double v) { x = v; }
	void SetY(double v) { y = v; }

	static int ccw(Point a, Point b, Point c){
		double area = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
								// (b-a)x(c-a)
		if (area < 0) return -1; // clockwise
		else if (are > 0) return 1; // counter-clockwise
		else return 0; // collinear
	}

	int compare(Point q1,  Point q2){
		double dy1 = q1.y - y;
		double dy2 = q2.y - y;

		if (dy1 == 0 && dy2 == 0) return 0; // p, q1, q2 horizontal
		else if (dy1 >= 0 && dy2 < 0) return -1; // q1 above p; q2 below p
		else if (dy2 >= 0 && dy1 < 0) return +1; // q1 below p; q2 above p
		else return -ccw(this, q1, q2);
	}
};

void ConvexHull(Point[] p, int N, stack<Point>& hull){
	std::sort(p, Point.Y_ORDER);
	std::sort(p, p[0].BY_PLOAR_ORDER);

	hull.push(p[0]);
	hull.push(p[1]);

	for (int i = 2; i < N; i++){
		Point top = hull.pop();
		while (Point.ccw(hull.peek(), top, p[i]) <= 0)
			top = hull.pop();
		hull.push(top);
		hull.push(p[i]);
	}
}
