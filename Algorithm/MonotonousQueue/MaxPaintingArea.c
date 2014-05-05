/*
问题：有n幢建筑，其高度分别为H1，...，Hn，其宽度为1，且这些建筑紧靠在一起，当前需要在这些建筑上刷一个非常大的矩形广告，
求矩形广告的最大值
*/

// naive method, O(N^3)
static int get_min(int *s, int start, int end)
{
    int i, min = s[start];

    for (i = start;i <= end;i++) {
        if (min > s[i])
            min = s[i];
    }
    return min;
}

int continous_sum_o3(int *s, int n)
{
    int i, j;
    int min, max = s[0];

    for (i = 0;i <= n - 1;i++) {
        for (j = i;j <= n - 1;j++) {
            min = get_min(s, i, j);
            if (max < min * (j - i + 1))
                max = min * (j - i + 1);
        }
    }

    return max;
}

