/*
子问题的递归结构的分析：设序列X=<x1, x2, …, xm>和Y=<y1, y2, …, yn>的一个最长公共子序列Z=<z1, z2, …, zk>，则：
1.  若xm=yn，则zk=xm=yn且Zk-1是Xm-1和Yn-1的最长公共子序列；
2.  若xm≠yn且zk≠xm ，则Z是Xm-1和Y的最长公共子序列；
3.  若xm≠yn且zk≠yn ，则Z是X和Yn-1的最长公共子序列。
其中Xm-1=<x1, x2, …, xm-1>，Yn-1=<y1, y2, …, yn-1>，Zk-1=<z1, z2, …, zk-1>。
用c[i,j]记录序列Xi和Yj的最长公共子序列的长度。其中Xi=<x1, x2, …, xi>，Yj=<y1, y2, …, yj>。
当i=0或j=0时，空序列是Xi和Yj的最长公共子序列，故c[i,j]=0。
*/

function LCSLength(X[1..m], Y[1..n])
    C = array(0..m, 0..n)
    for i := 0..m
       C[i,0] = 0
    for j := 0..n
       C[0,j] = 0
    for i := 1..m
        for j := 1..n
            if X[i] = Y[j]
                C[i,j] := C[i-1,j-1] + 1
            else
                C[i,j] := max(C[i,j-1], C[i-1,j])
    return C[m,n]
function backtrack(C[0..m,0..n], X[1..m], Y[1..n], i, j)
    if i = 0 or j = 0
        return ""
    else if  X[i] = Y[j]
        return backtrack(C, X, Y, i-1, j-1) + X[i]
    else
        if C[i,j-1] > C[i-1,j]
            return backtrack(C, X, Y, i, j-1)
        else
            return backtrack(C, X, Y, i-1, j)
