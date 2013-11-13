///////////////////////////////////////////////////////////////////////
typedef struct NODE *link;
struct NODE { 
	int item; 
	link l, r; 
};

link Alloc(int item, link l, link r){
	link n = (link)malloc(sizeof(node));

	n->item = item;
	n->l = l;
	n->r = r;
	return n;
}

link build_league_tree(int arr[], int l, int r){
	int mid = (l+r)/2;
	int l_val, r_val;

	link x = Alloc(arr[mid], NULL, NULL);

	if (l == r)
		return x;
	x->l = build_league_tree(arr, l, mid);
	x->r = build_league_tree(arr, mid+1, r);

	l_val = x->l->item;
	r_val = x->r->item;
	if (l_val > r_val)
		x->item = l_val;
	else
		x->item = r_val;

	return x;
}
