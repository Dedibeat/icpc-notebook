// Mergeable dynamic segment trees over positions [tl, tr] (sum).
// Roots are ints (0 = empty). merge(u,v,..) destroys v and returns u.
// Pool: 40*maxn nodes fits ~maxn points over a range of size ~1e9 with merges.
// Pitfalls: reset tp=1 and roots between test cases; merge reuses u's nodes.
const int maxn = 2e5 + 5;
struct node {
	int s, l, r;
	node() : s(0), l(0), r(0) {}
} tree[40 * maxn];
int tp = 1;
void upd(int &u, int tl, int tr, int pos, int delta) 
{
	if(!u) u = tp++;
	tree[u].s += delta;
	if(tl < tr) {
		int tm = (tl + tr) / 2;
		if(pos <= tm) upd(tree[u].l, tl, tm, pos, delta);
		else upd(tree[u].r, tm + 1, tr, pos, delta);
	}
}
int query(int u, int tl, int tr, int l, int r)
{
	if(l > r || u == 0) return 0;
	if(l == tl && r == tr) return tree[u].s;
	int tm = (tl + tr) / 2;
	return query(tree[u].l, tl, tm, l, min(r, tm)) +
			query(tree[u].r, tm + 1, tr, max(l, tm + 1), r);
}
int merge(int u, int v, int tl, int tr)
{
	if(!u || !v) return u | v;
	tree[u].s += tree[v].s;
	if(tl < tr) {
		int tm = (tl + tr) / 2;
		tree[u].l = merge(tree[u].l, tree[v].l, tl, tm);
		tree[u].r = merge(tree[u].r, tree[v].r, tm + 1, tr);
	}
	return u;
}
