//How do i find all the positions of a substring in a string?

/*
Two other answers are correct but they are very slow and have O(N^2) complexity. 
But there is Knuth-Morris-Pratt algorithm which finds all substrings in O(N) complexity.

Also there is another algoritm so called "Z-function" with O(N) complexity, but I couldn't find English source of this algorithm
(maybe because there is also another more famouse thing with same name - the Z-function of Riman), 
so will just put its code here and explain what it do.
*/
void calc_z (string &s, vector<int> & z)
{
    int len = s.size();
    z.resize (len);

    int l = 0, r = 0;
    for (int i=1; i<len; ++i)
        if (z[i-l]+i <= r)
            z[i] = z[i-l];
        else
        {
            l = i;
            if (i > r) r = i;
            for (z[i] = r-i; r<len; ++r, ++z[i])
                if (s[r] != s[z[i]])
                    break;
            --r;
        }
}
int main()
{
    string main_string = "some string where we want to find substring or sub of string or just sub";
    string substring = "sub";
    string working_string = substring + main_string;
    vector<int> z;
    calc_z(working_string, z);

    //after this z[i] is maximal length of prefix of working_string
    //which is equal to string which starting from i-th position of
    //working_string. So the positions where z[i] >= substring.size()
    //are positions of substrings.

    for(int i = substring.size(); i < working_string.size(); ++i)
        if(z[i] >=substring.size())
            cout << i - substring.size() << endl; //to get position in main_string
}
