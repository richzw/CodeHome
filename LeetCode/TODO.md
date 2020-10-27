// Q1

第一行是一个数n，表示开始时有多少根木棍(1<=n<=3000)第二行有n个数，从第1个到第n个分别表示从左到右的木棍长度。对任意木棍的长度l，有1<=l<=3000。

> 输入:   5
       3 5 13 9 12
> 输出    1

说明:  你可以将长度为13的木棍折成长度分别为5和8的两根木棍，最终得到的排列是3 5 5 8 9 12

hint: 单调栈

// Q2

请将切成不同长度的棒子拚接起来，做出长度相同的棒子，但是要考虑拚接起来的度必须是最短的。换句话说，就是尽量做出更多长度相同的棒子。 (POJ 1011)

// Q3

有一条长度为n的木棍，已知木棍的销售价格Pi与木棍长度i有关,i = 1,2,3,...n.问，怎样切割能获得最大收益

|切割长度（seg） |	1   |	2 |	3 |	4 |	5  |	6   |	7   |	8   |	9   |	10|
| ----         | ---- |----|----  |  ----|  -----|  -----|  ----| ---- | ---- |----|
|销售价格（pi）  |	1   |	5 |	8 |	9 |	10 | 	17  |	17  |	20  | 	24  | 	30|

profit[n] = max(pi[i] + profit[length - seg[i]])

```c
int Cut_Common(int seg[], int pi[], int arr_len, int source_len)
{
    if (source_len == 0)
        return 0;
	int tmp = -1;
	for (int i = 0; i < arr_len; ++i)
	{
        if (source_len - seg[i] >= 0)
		    tmp = max(tmp, pi[i] + Cut_Common(seg, pi, arr_len, source_len - seg[i]));
```

```c
int _Cut_Dynamic_DownToTop(int seg[], int pi[], int arr_len, int length, int dump[])
{
    int tmp;
    dump[0] = 0;
    for (int i = 1; i <= length; ++i)
    {
        tmp = -1;   
        for (int j = 0; j < arr_len; ++j)
        {
            if (i - seg[j] >= 0)
                tmp = max(tmp, pi[j] + dump[i - seg[j]]);               
        
        }
        dump[i] = tmp;
 
    }
    return dump[length];
}
 
int Cut_Dynamic_DownToTop(int seg[], int pi[], int arr_len, int length)
{
    int *dump = (int *)malloc(sizeof(int)*length + 1);
    int tmp = _Cut_Dynamic_DownToTop(seg, pi, arr_len, length, dump);
    free(dump);
    return tmp;

```

```c
int _Cut_Dynamic_TopToDown(int seg[], int pi[], int arr_len, int length, int dump[])
{
    if (dump[length] >= 0)
        return dump[length];
    int tmp = -1;
    for (int i = 0; i < arr_len; ++i)
    {
        if (length - seg[i] >= 0)
            tmp = max(tmp, pi[i] + _Cut_Dynamic_TopToDown(seg, pi, arr_len, length-seg[i], dump));
    }
    dump[length] = tmp;
    return dump[length];
}
 
int Cut_Dynamic_TopToDown(int seg[], int pi[], int arr_len, int length)
{
    int *dump = (int *)malloc(sizeof(int)*length+1);
    for (int i = 0; i <= length; ++i)
    {
        dump[i] = -1;
    }
    dump[0] = 0;
    int tmp = _Cut_Dynamic_TopToDown(seg, pi, arr_len, length, dump);
    free(dump);
    return tmp;
```
                  
