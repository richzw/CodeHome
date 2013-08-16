  1 const int n = 20;
  2 vector<int>  v(n);
  3 v[0] = 1;
  4
  5 int i2 = 0;
  6 int i5 = 0;
  7
  8 int x2 = 2*v[i2];
  9 int x5 = 5*v[i5];
 10
 11 for (int i = 1; i != n; ++i)
 12 {
 13     int m = min(x2, x5);
 14     v[i] = m;
 15
 16     if (x2 == m){
 17         ++i2;
 18         x2 = 2 * v[i2];
 19     }
 20     if (x5 == m){
 21         ++i5;
 22         x5 = 5 * v[i5];
 23     }
 24 }
