/*
Q:有一个棵树，不一定是二叉树，有n个节点，编号为0到n-1。有一个数组A，数组的索引为0到n-1，
数组的值A[i]表示节点i的父节点的id，根节点的父节点id为-1。给定数组A，求得树的高度。

这个题目我们首先把数组写出来，然后进一步分析，就很明了了，如下例子：
333-12
01234
根据题意：
	* 节点0,1,2的父节点为3
	* 节点3是根节点
	* 节点4的父节点为2
一个很直接的解法是，遍历数组A中的每一个元素，回溯到根节点，得到这个节点的高度。遍历完毕数组之后，取最大的，就是树的高度。
上面的例子大概过程如下：
	* 0->3->-1，得到0到到根的高度为2，同理1->3->-1, 2->3->-1
	* 3->-1，高度就是1
	* 4->2->3->-1，得到高度3
*/

int getDepthRecur(int tree[], int index, int height[]){
	if (height[index] != -1)
		return height[index];
	
	if (tree[index] == -1)
		height[index] = 0;
	else
		height[index] = getDepthRecur(tree, tree[index], height) + 1;
			
	return height[index];
}

int getDepth(int tree[], int len){
	int* height = new int[len];

	for (int i = 0; i < len; ++i)
		height[i] = -1;

	int max_dep = -1;
	for (int i = 0; i < len; ++i)
		if (height[i] == -1)
			max_dep = max(max_dep, getDepthRecur(tree, i, height));

	return max_dep;
}
