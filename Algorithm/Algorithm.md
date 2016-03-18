分享学习算法的几个方法：
①对比（贪心：最优子结构+局部最优，动态规划：最优独立重叠子结构+全局最优），
②联系（如数组+链表=Hash表，广搜+队列=Dijkstra，广搜+权重队列=A*），

学习一个算法，先知其解决什么，后知其解决策略 。如图算法中，
①广搜：一层一层往外遍历，寻找最短路径，策略：队列，
②最小生成树：最小代价连接所有点，策略：贪心（Prim：贪心+权重队列），
③Dijkstra：寻找单源最短路径，策略：贪心+非负权重队列，④
Floyd：多结点对的最短路径，策略：动态规划。

Well, if I was to interview someone and asked this question, my logic would be something like this. If the candidate can do it using sort(), it's a good sign anyway, so it gives a positive point. The next thing I'd ask is what the complexity of the solution. If the candidate says it's O(N), that would be a huge negative point that would turned the score to negative, and at that point I'd probably decide that we don't want such an employee. If the candidate can't answer that because they don't know what complexity sort() is, but don't make any wrong assumptions, that's still a negative point, but not that bad.

If the candidate gives the right answer, then I'd ask about possible ways to improve the complexity. Can it be done in linear time? Can it be done with no extra space? Can we get both? And I listen to their ideas. Possible reactions that may come up:

- No, it can't be done in linear time, period.—Huge negative point. Nobody needs programmers that give up so easily.
It's possible if use some kind of linear-time sorting algorithm.—Good. At least they know that there are linear-time sorting algorithms out there.
- Like the counting sort maybe?—Very good. They don't only know that there are such, but they can also name the right one for this problem.
- But we can only use the counting sort if the values are within a given range, and here the number of publications is unlimited, so the counting sort won't work.—Mild negative point. Come on, try harder!
- But wait a minute. It is really unlimited? How many scientists out there actually do have publications with billions of citations?—Very good. Not only thinking about algorithms, but actually trying to optimize the algorithm for the real life task beyond the algorithmic problem.
- So we can use an array of some size that grows as needed when we encounter citation counts that don't fit.—Good, not the best idea, but one that would really work just as fine.
- Oh, and it also looks like we don't need to do any actual sorting. We only need to know the less-than-or-equal or greater-than-or-equal counts in order to find the answer!—Very good.
- And we don't even need all of the counts because we only comparing them to possible answers which lie in the [0, N] interval, so we may consider every publication having more than N citation as having exactly N for our purpose.—Brilliant. Even if they don't come up with the actual implementation of that in time, but will show the ability to eventually do it, I'd probably decide it's the right candidate.
- And I kind of have a feeling that it's possible to do with constant space by reusing the space we already have in the array, but can't exactly figure out how to do it.—Good. Even if they can't do it, they seem to have good programmer's intuition.
And of course, if they instantly come up with an O(N) time O(1) space solution, I'd become real suspicious. A good programmer can come up with one all right, but hardly instantly.

In the end, what matters is the right logic and the ability to implement that logic, no matter whether they can actually complete it during the interview or not.

Oh, and a good follow-up question is: is it possible that there are more than one valid value for h? This problem hints that it is, but the correct answer that it isn't.

P. S. Not that I have ever really interviewed someone, but I have more than 10 years of real job experience and I saw many different programmers, so I feel like I know what to look for.
