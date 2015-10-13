
// Newton method
/*
Xn+1 = 1/2(Xn + S/Xn)
https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
*/
int sqrt(int x) {
    double y,z(1.0);
    while(int(y)-int(z)){
        y=z;
        z=double(x)/2/y+y/2;
    }
    return int(y);
}

// binary search method 
double sqaure_root_of(double value)
{
     assert(value >= 1);
     double lo = 1.0;
     double hi = value;

     while( hi - lo > 0.00001)
     {
          double mid = lo + (hi - lo) / 2 ;
          std::cout << lo << "," << hi << "," << mid << std::endl;
          if( mid * mid - value > 0.00001)    //this is the predictors we are using 
          {
              hi = mid;
          } else {
              lo = mid;
          }

     }

    return lo;
 }
