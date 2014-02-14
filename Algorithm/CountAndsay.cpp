/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.
Note: The sequence of integers will be represented as a string.
*/

class MySolution {
public:
    string countAndSay(int n) {
        if(n==1)
        {
            return "1";
        }
        else if(n==2)
        {
            return "11";
        }
        else
        {
            string str = countAndSay(n-1);
            string result;
            int pre;
            int cur=str[0]-'0';
            int count=1;
            for(int i=1;i<str.size();i++)
            {
                pre=cur;
                cur=str[i]-'0';
                if(pre==cur)
                {
                    count++;
                }
                else
                {
                    result.push_back(count+'0');
                    result.push_back(pre+'0');
                    count=1;
                }
            }
            result.push_back(count+'0');
            result.push_back(cur+'0');
            return result;
        }
    }
};
