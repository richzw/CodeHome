/*
Q: 给个数组，打乱了，比如：索引 0 1 2 3 4；值 3 2 1 4 0 。数组的值是下次跳的索引位置，
   这样的话数组有环，比如 0 -> 3 -> 4 -> 0 1 -> 2 -> 1， 求最长环的长度。
*/

// basic solution 1
class Solution
{
public:
    int solution(int * A, int len)
    {
        if(NULL == A || len <= 0)
        {
            return 0;
        }
 
        int maxSet = 1, count = 0;
        for(int i = 0, j, index; i < len; ++i)
        {
            index = i;
            while(A[index] >= 0)
            {
                ++count;
                j = index;
                index = A[index];
                A[j] = -1;
            }
            maxSet = count > maxSet ? count : maxSet;
            count = 0;
        }
        return maxSet;
    }
};

//A: Union-Find.
class Solution
{
private:
    class UnionSet
    {
    public:
        int * father, * num, maxSize;
        // make set
        UnionSet(int len):maxSize(1)
        {
            father = new int [len];
            num = new int [len];
            for(int i = 0; i < len; ++i)
            {
                num[i] = 1;
            }
            for(int i = 0; i < len; ++i)
            {
                father[i] = i;
            }
        }
        ~UnionSet()
        {
            delete [] father;
            delete [] num;
        }
        // find set
        int findSet(int x)
        {
            if(x != father[x])
            {
                father[x] = findSet(father[x]);
            }
            return father[x];
        }
        // union
        void unionSet(int a, int b)
        {
            int x = findSet(a);
            int y = findSet(b);
            if(x == y)
            {
                return;
            }
            if(num[x] >= num[y])
            {
                father[y] = x;
                num[x] += num[y];
                maxSize = num[x] > maxSize ? num[x]: maxSize;
            }else
            {
                father[x] = y;
                num[y] += num[x];
                maxSize = num[y] > maxSize ? num[y]: maxSize;
            }
        }
    };
 
public:
    int solution(int * A, int len)
    {
        if(NULL == A || len <= 0)
        {
            return 0;
        }
        UnionSet unionSet(len);
        for(int i = 0; i < len; ++i)
        {
            if(A[i] < len)
            {
                unionSet.unionSet(i,A[i]);
            }
        }
        return unionSet.maxSize;
    }
};

// Simple Test
void main()
{
    Solution testCase;
 
    int A[] = {1,2,3,4,5,6};
    printf("%d\n", testCase.solution(A,6));
 
    int B[] = {1,4,5,0,2,6};
    printf("%d\n", testCase.solution(B,6));
}
