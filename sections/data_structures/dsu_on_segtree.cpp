// Mergeable dynamic segment trees (sum) over positions [0, POSMAX].
// Each set is a root id (0 = empty). Call with defaulted bounds:
//   upd(root[v], pos, +1);  query(root[v], l, r);  root[u] = merge(root[u], root[v]);
// merge destroys v's tree and returns the combined root. Total O(inserts*logP).
// Pool: 40*maxn nodes fits ~maxn inserts for POSMAX ~ 1e9; shrink to fit ML.
// Pitfalls: reset tp = 1 and all roots to 0 between test cases.
const int maxn = 2e5 + 5, POSMAX = 1e9;
struct node {
	int s, l, r;
	node() : s(0), l(0), r(0) {}
} tree[40 * maxn];
int tp = 1;
void upd(int &u, int pos, int delta, int tl = 0, int tr = POSMAX)
{
	if(!u) { u = tp++; tree[u] = node(); } // fresh node: makes tp reset safe
	tree[u].s += delta;
	if(tl < tr) {
		int tm = tl + (tr - tl) / 2;
		if(pos <= tm) upd(tree[u].l, pos, delta, tl, tm);
		else upd(tree[u].r, pos, delta, tm + 1, tr);
	}
}
int query(int u, int l, int r, int tl = 0, int tr = POSMAX)
{
	if(l > r || u == 0) return 0;
	if(l == tl && r == tr) return tree[u].s;
	int tm = tl + (tr - tl) / 2;
	return query(tree[u].l, l, min(r, tm), tl, tm) +
			query(tree[u].r, max(l, tm + 1), r, tm + 1, tr);
}
int merge(int u, int v, int tl = 0, int tr = POSMAX)
{
	if(!u || !v) return u | v;
	tree[u].s += tree[v].s;
	if(tl < tr) {
		int tm = tl + (tr - tl) / 2;
		tree[u].l = merge(tree[u].l, tree[v].l, tl, tm);
		tree[u].r = merge(tree[u].r, tree[v].r, tm + 1, tr);
	}
	return u;
}
