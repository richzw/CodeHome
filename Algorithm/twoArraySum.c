/*
Q: 两个数组，从每个数组中取一个数相加，求最大的前k个和 
     数组A：1,2,3 
     数组B：4,5,6 
     则最大的前2个和：9,8。
/*
solution 1:
B数组排序，从大到小。 构造一个大顶堆h。对于i=0,1,2,...,len(A)-1，把三元组(A[i]+B[0], i, 0)放入堆，按三元组第一个元素排大小。 
  
每次从堆里取出堆顶元素，设其为(s,i,j)。输出s。 
设m=j+1。如果m小于B的长度减一，那么将三元组(A[i]+B[m], i, m)压入堆中。 重复，直到输出了k个数为止。 
时间复杂度：O(len(B)*log(len(B)) + len(A) + k*log(len(A))) 
*/
/*
That can be easily done in O(k*logk). I'll only assume arrays are sorted in descending order, to simplify notation.
The idea is simple. We'll find 1st, 2nd, .., k-th maximum values one by one.
But to even consider pair (i, j) we need to have both (i-1, j) and (i, j-1) already selected, because they both are greater or equal than (i, j).
It's much like if we push all n*m pairs into the heap and then remove max k times. Only we don't need all n*m pairs.
*/
void GetKthLargestSum(int arrA[], int lenA, int arrB[], int lenB, int k){
	if (arrA == NULL || lenA == 0 || lenB == NULL || lenB == 0)
		return;

	// sort array A and B, descending order...
	qsort(arrA, lenA, sizeof(int), compare);
	qsort(arrB, lenB, sizeof(int), compare);

	// key: sum(A, B), value: pair<indexOfA, indexOfB>
	priority_queue<int, pair<int, int> > maxHeap;

	int idxA = 0, idxB = 0;
	maxHeap.push(pair<int, pair<int, int> >(arrA[0]+arrB[0], make_pair(idxA, idxB)));
	for (int idx = 0; idx < k; ++idx){
		pair<int, pair<int, int> > val = maxHeap.top();
		cout << val.first << " ";
		maxHeap.pop();

		maxHeap.push(pair<int, pair<int, int> >(arrA[val.second.first+1]+arrB[val.second.second], make_pair(val.second.first+1, val.second.second)));
		maxHeap.push(pair<int, pair<int, int> >(arrA[val.second.first]+arrB[val.second.second+1], make_pair(val.second.first, val.second.second+1)));
	}
	// TODO: 1. Duplicated pairs can be added to the heap, this can be prevented with hash.
	//		 2. Indexes need to be validated, e.g. that max.i + 1 < arrA.length.
}

/*
solution 2:
假设两个数组都是升序的） 
二分sum的下限x。 
对于这个x，一个指针从A数组的头开始往后扫，一个指针从B数组的尾开始往前扫，这样扫一次可以O(A+B)求出不小于x的sum的个数t。 
根据t与k的大小关系继续二分x。 最后确定了x后可以扫一次并求出所有数对。 O((A+B)lg(sum)+k)
*/


/*
All in All: 
1、碰到这个问题的一般思路是，把m*n个数先求出来，然后用Nth-Elemnet，找出第k大的数。Nth-Element就是快排变形的那个partition，
线性时间，这里不延伸讲了。这样的话时间复杂度O(m*n)，空间复杂度O(m*n)。

2、对于第一种方法，时间复杂度还好说，空间复杂度实在问题比较大，是否可以不求出这m*n个元素就直接找打第K大的数呢？
可以这样，先对A，B分别排序。复杂度n*log(n) + m*log(m)，排序后我们就发现第k大的数一定在
Min = A[0] + B[0] <= C[k] <= A[n] + B[m] = Max，而且从Min到Max，K是递减，如果用二分法找这个C[k]，然后在A和B中判断，
有多少个数比C[k]大。如果恰好有k-1个数比C[k]大，则C[k]是第K大的数。考虑有相等的情况，如果比C[K]大的数不到K个，
而比C[K]小的数不到m*n - k个，则说明等于C[K]的数有多个（当然直接判断=也可以），那么C[K]就是第k大的数。

总结一下这个思路，就是在Min和Max之间，二分找这个和，然后在排序好的数组A,B中，统计有多少个数大于这个和。
在这个思路的基础上，如何统计有多少个数的和大于给定的数C[k]呢？我们可以枚举数组A中的元素，然后利用二分，
在数组B中找到C[k] - A[i]对应的元素B[j]，那么所有比B[j]大的元素同A[i]的和，都大于C[k]。
这样就可以写出一个n*log(m)*log(Max - Min) + n*log(n) + m*log(m)的程序来解决这个问题，空间复杂度O(1)

3、对于方法2，有一个简单的优化，就是如果n > m，也就是数组B的长度大于数组A的长度，如果枚举数组B，效率会更高，
空间还是O(1)，时间变为了min(m,n)*log(max(n,m))*log(max - min) + n*log(n) + m*log(m)

4、对于方法2和3，都还可以进一步优化，优化的关键点在于：枚举数组A，在数组B中二分找一个数。如果改用头尾指针的方式，
平摊下来是线性的。方法如下：
先用一个指针指向数组A的头，一个指向数组B的尾，如果A[0] + B[m] < C[k]，A的指针后移，
判断A[1] + B[m]，如果A[0] + B[m] > C[k]，则B的指针前移，判断A[0] + B[m-1]。简单说就是< C[k]，A的指针后移，> C[k]，
B的指针前移。不过问题的关键在于计数，同时统计大于C[k]的小于C[k]的数有多少个。如果A[0] + B[m] < C[k]，
则A[0] + B[0],B[1]......B[m-1]都小于<C[k]，小于的计数+m,如果A[0] + B[m] > C[k]，则A[1],A[2]......A[n]+B[m]都大于C[k]，
大于计数+n，这样，就可以写出一个(m+n)*log(Max-Min)+ n*log(n) + m*log(m)的程序，来解决这个问题。

到此为止，优化到头了么？其实此问题可以转为在杨氏矩阵中找第k大的值，问题还有优化的空间，关键在于Log(Max - Min)，
可以优化到Log(m*n)，后者适用范围就不仅仅是整数了，实数范围都可以
*/
/*
http://stackoverflow.com/questions/18557175/how-to-find-pair-with-kth-largest-sum
I start with a simple but not quite linear-time algorithm. We choose some value between array1[0]+array2[0] and array1[N-1]+array2[N-1]. 
Then we determine how many pair sums are greater than this value and how many of them are less. 
This may be done by iterating the arrays with two pointers: pointer to the first array incremented when sum is too large and pointer to the second array decremented when sum is too small.
Repeating this procedure for different values and using binary search (or one-sided binary search) we could find Kth largest sum in O(N log R) time,
where N is size of the largest array and R is number of possible values between array1[N-1]+array2[N-1] and array1[0]+array2[0].
This algorithm has linear time complexity only when the array elements are integers bounded by small constant.

We could estimate value range with the following trick: get every second element from each array and try to 
find the pair sum with rank k/4 for these half-arrays (using the same algorithm recursively). Obviously this should give some approximation for needed value range.
And in fact slightly improved variant of this trick gives range containing only O(N) elements. 
This is proven in following paper: "Selection in X + Y and matrices with sorted rows and columns" by A. Mirzaian and E. Arjomandi. 
This paper contains detailed explanation of the algorithm, proof, complexity analysis, and pseudo-code for all parts of the algorithm except Quickselect.
If linear worst-case complexity is required, Quickselect may be augmented with Median of medians algorithm.

This algorithm has complexity O(N). If one of the arrays is shorter than other array (M < N) we could assume that
this shorter array is extended to size N with some very small elements so that all calculations in the algorithm use size of the largest array.
We don't actually need to extract pairs with these "added" elements and feed them to quickselect, which makes algorithm a little bit faster but does not improve asymptotic complexity.

If k < N we could ignore all the array elements with index greater than k. In this case complexity is equal to O(k). 
If N < k < N(N-1) we just have better complexity than requested in OP. If k > N(N-1), we'd better solve the opposite problem: k'th smallest sum.
*/
int qceil(int x)
{
	return (x + 3) / 4;
}

int qhigh(int x, int n)
{
	if (n & 1) // odd
		return qceil(x + 2 * n + 1);
	else // even
		return n + 1 + qceil(x);
}

typedef std::vector<int> Vec;

struct Ranks
{
	int ra_less;
	int rb_more;
	Vec l;

	Ranks(const Vec& a1, const Vec& a2, int a, int b)
	{
		int n = a1.size() - 1;
		ra_less = 0;
		rb_more = n * n;
		l.reserve(12 * n + 1);
		l.push_back(0);

		int j = n;
		for (int i = 1; i <= n; ++i)
		{
			while (j && a1[i] + a2[j] <= a)
				--j;

			ra_less += j;
			int jj = j;

			while (jj && a1[i] + a2[jj] < b)
			{
				l.push_back(a1[i] + a2[jj]);
				--jj;
			}

			rb_more -= jj;
		}
	}
};

Vec half(const Vec& a)
{
	Vec res;
	res.reserve(2 + (a.size() - 1) / 2);
	res.push_back(0);

	for (int i = 1; i < a.size(); i += 2)
		res.push_back(a[i]);

	if (a.size() & 1)
		res.push_back(a[a.size() - 1]);

	return res;
}

struct AB
{
	int a;
	int b;
};

AB biselect(const Vec& a1, const Vec& a2, int k1, int k2)
{
	AB res;
	int n = a1.size() - 1;
	assert(n > 0);

	if (n == 1)
	{
		res.a = res.b = a1[1] + a2[1];
	}
	else if (n == 2)
	{
		Vec l {a1[1] + a2[1], a1[1] + a2[2], a1[2] + a2[1], a1[2] + a2[2]};
		std::nth_element(l.begin(),
			l.end() - k1,
			l.end());
		res.a = l[4 - k1];
		std::nth_element(l.begin(),
			l.end() - k2,
			l.end());
		res.b = l[4 - k2];
	}
	else
	{
		int k1_half = qhigh(k1, n);
		int k2_half = qceil(k2);
		AB ab = biselect(half(a1), half(a2), k1_half, k2_half);
		Ranks ranks(a1, a2, ab.a, ab.b);
		int r1 = k1 + ranks.rb_more - n * n;
		int r2 = k2 + ranks.rb_more - n * n;

		if (ranks.ra_less <= k1 - 1)
			res.a = ab.a;
		else if (r1 <= 0)
			res.a = ab.b;
		else
		{
			std::nth_element(ranks.l.begin() + 1,
				ranks.l.end() - r1,
				ranks.l.end());
			res.a = *(ranks.l.end() - r1);
		}

		if (ranks.ra_less <= k2 - 1)
			res.b = ab.a;
		else if (r2 <= 0)
			res.b = ab.b;
		else
		{
			std::nth_element(ranks.l.begin() + 1,
				ranks.l.end() - r2,
				ranks.l.end());
			res.b = *(ranks.l.end() - r2);
		}
	}

	return res;
}

int select(const Vec& a1, const Vec& a2, int k)
{
	assert(a1.size() == a2.size());
	AB ab = biselect(a1, a2, k, k);
	assert(ab.a == ab.b);
	return ab.a;
}

int check(const Vec& a1, const Vec& a2, int k)
{
	int n = a1.size() - 1;
	Vec sum;
	sum.reserve(n * n);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			sum.push_back(a1[i] + a2[j]);

	std::nth_element(sum.begin(),
		sum.end() - k,
		sum.end());
	return *(sum.end() - k);
}

#include <random>

int sovle_two_arrays_sum()
{
	std::random_device rd;
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(1, 6);

	int n = 100000;
	Vec a1, a2;
	a1.reserve(n+1);
	a2.reserve(n+1);
	int x = 1000;

	a1.push_back(0);
	for (int i = 0; i < n; ++i)
	{
		x -= uniform_dist(e1);
		a1.push_back(x);
	}

	x = 1000;

	a2.push_back(0);
	for (int i = 0; i < n; ++i)
	{
		x -= uniform_dist(e1);
		a2.push_back(x);
	}

	std::cout << select(a1, a2, 1 + n * n / 7) << '\n'
		/*<< check(a1, a2, 1 + n * n / 7) << '\n'*/;

	return 0;
}
