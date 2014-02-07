//Clone a graph. Input is a Node pointer. Return the Node pointer of the cloned graph.
struct GNode {
	vector<GNode*> neighbors;
};

typedef unordered_map<GNode *, GNode *> g_map; // avoid cycle copy node
GNode* copy_graph(GNode* graph){
	if (graph == NULL)
		return NULL;

	g_map map;
	queue<GNode*> q;
	q.push(graph);

	GNode* g_copy = new GNode();
	map[graph] = g_copy;

	while (!q.empty()){
		GNode* node = q.front();
		q.pop();
		int cnt = node->neighbors.size();

		for (int i = 0; i < cnt; ++i){
			GNode* nei = node->neighbors[i];

			if (map.find(nei) == map.end()){
                GNode *p = new GNode();
                map[node]->neighbors.push_back(p);
                map[nei] = p;
                q.push(nei);
            } else {     // a copy already exists
                map[node]->neighbors.push_back(map[nei]);
            }
		}
	}

	return g_copy;
}
