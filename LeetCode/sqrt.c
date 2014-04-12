int sqrt(int x) {
    double y,z(1.0);
    while(int(y)-int(z)){
        y=z;
        z=double(x)/2/y+y/2;
    }
    return int(y);
}
