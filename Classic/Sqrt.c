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
 
 x = 2^ceil(numbits(N)/2)
loop:
    y = floor((x + floor(N/x))/2)
    if y >= x
        return x
    x = y
 
 
