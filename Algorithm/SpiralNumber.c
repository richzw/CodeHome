/*
Determine the index of a grid coordinate centered at 0,0 and increasing in a spiral around the origin

25|26|27|28|29|30
24| 9|10|11|12|31
23| 8| 1| 2|13|32
22| 7| 0| 3|14|33
21| 6| 5| 4|15|34
20|19|18|17|16|35
 ........     |36
*/

int spiralNumber(int x, int y)
{
    var pos,squ;
    // Horizontal row at top
    if(y>=0 && ( x >= 1-y && x<y ) ) {
        pos = x+y-1;
        squ = (2 *y-1)*(2*y-1);
    // Horizontal row at bottom
    } else if( y < 0 && ( x >= y && x<= -y ) ) {
        pos = -x-y;
        squ = 4*y*y;
    // Vertical row on right
    } else if( x >0 ) {
        pos = -x-y;
        squ = 4*x*x;
    // Vertical row on left
    } else {
        squ = (1-2*x)*(1-2*x);
        pos = x+y-1;
    }
    return squ+pos;
}
