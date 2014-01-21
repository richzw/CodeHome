/*
Describe an algorithm that takes an unsorted array of axis‐aligned rectangles and
returns any pair of rectangles that overlaps, if there is such a pair. Axis‐aligned
means that all the rectangle sides are either parallel or perpendicular to the x‐ and
y‐axis. You can assume that each rectangle object has two variables in it: the x‐y
coordinates of the upper‐left corner and the bottom‐right corner.
*/


//Given a 2D point and a rectangle, determine if the point is inside the rectangle.
/*
 the rectangle’s center is translated to the origin, 
 then the rectangle is rotated such that it is axis-aligned with the major axes.
 The rotation equation can be written as x’ = ux*x + uy*y and y’ = vx*x + vy*y, where (x,y) is the original point, (x’,y’) is the rotated point, 
 (ux,uy) and (vx,vy) are both the normalized orthogonal vector of the axes of the rectangle (see figure above).
*/


bool is_point_in_rectangle(const Rect& rect, const Point& p) {
  Vector2d P1(rect.p1.x, rect.p1.y);
  Vector2d P2(rect.p2.x, rect.p2.y);
  Vector2d P3(rect.p3.x, rect.p3.y);
  Vector2d P4(rect.p4.x, rect.p4.y);
  Vector2d P(p.x, p.y);
 
  Vector2d P1_P4 = P1 - P4;
  Vector2d P3_P4 = P3 - P4;
  Vector2d TWO_P_C = 2.0*P - P1 - P3;    // TWO_P_C=2P-C, C=Center of rectangle
 
  return (P3_P4.Dot(TWO_P_C - P3_P4) <= 0 && P3_P4.Dot(TWO_P_C + P3_P4) >= 0) &&
         (P1_P4.Dot(TWO_P_C - P1_P4) <= 0 && P1_P4.Dot(TWO_P_C + P1_P4) >= 0);
}
