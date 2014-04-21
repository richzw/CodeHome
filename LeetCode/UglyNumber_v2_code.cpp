const int n = 20;
vector<int>  v(n);
v[0] = 1;

int i2 = 0;
int i5 = 0;

int x2 = 2*v[i2];
int x5 = 5*v[i5];

for (int i = 1; i != n; ++i)
{
    int m = min(x2, x5);
    v[i] = m;

    if (x2 == m){
        ++i2;
        x2 = 2 * v[i2];
    }
    if (x5 == m){
        ++i5;
        x5 = 5 * v[i5];
    }
}
