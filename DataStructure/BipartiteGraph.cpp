/*
Hungarian Algorithm

For Maximum matching, BFS and DFS

// Ref: http://www.renfei.org/blog/bipartite-matching.html
*/

// 顶点、边的编号均从 0 开始
// 邻接表储存

struct Edge
{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w):from(f), to(t), weight(w) {}
};

vector<int> G[__maxNodes]; /* G[i] 存储顶点 i 出发的边的编号 */
vector<Edge> edges;
typedef vector<int>::iterator iterator_t;
int num_nodes;
int num_left;
int num_right;
int num_edges;
