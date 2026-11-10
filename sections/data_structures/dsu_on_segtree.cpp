// Mergeable dynamic segment trees (sum) over positions [0, POSMAX].
// Each multiset is a root id (0 = empty). upd changes one position; query(u,l,r)
// sums the half-open position interval [l,r); merge combines disjoint roots and
// invalidates v.
// Example: upd(a,5,2); upd(b,7,1); a=merge(a,b); query(a,5,8)==3.
// Total O(inserts*logP); merging all roots is proportional to touched nodes.
// Pool grows as needed. Use deque so references survive allocation.
// Pitfalls: reset tp = 1 and all roots to 0 between test cases.
const int POSMAX = 1e9;
struct node {
	long long s = 0;
	int l = 0, r = 0;
};
deque<node> tree(1);
int tp = 1;
void upd(int &u, int pos, long long delta, int tl = 0, int tr = POSMAX + 1)
{
	if(!u) {
		u = tp++;
		if(u == (int)tree.size()) tree.emplace_back();
		else tree[u] = {};
	}
	tree[u].s += delta;
	if(tr - tl > 1) {
		int tm = tl + (tr - tl) / 2;
		if(pos < tm) upd(tree[u].l, pos, delta, tl, tm);
		else upd(tree[u].r, pos, delta, tm, tr);
	}
}
long long query(int u, int l, int r, int tl = 0, int tr = POSMAX + 1)
{
	if(!u || l >= r || r <= tl || tr <= l) return 0;
	if(l <= tl && tr <= r) return tree[u].s;
	int tm = tl + (tr - tl) / 2;
	return query(tree[u].l, l, r, tl, tm) + query(tree[u].r, l, r, tm, tr);
}
int merge(int u, int v)
{
	if(!u || !v) return u | v;
	tree[u].s += tree[v].s;
	tree[u].l = merge(tree[u].l, tree[v].l);
	tree[u].r = merge(tree[u].r, tree[v].r);
	return u;
}
