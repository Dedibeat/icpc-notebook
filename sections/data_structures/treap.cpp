// Implicit treap: the inorder traversal is a sequence; subtree sizes are keys.
// split(t,l,r,k) puts the first k values in l and the rest in r; merge(t,l,r)
// concatenates l then r. reverse(t,l,r) reverses [l,r).
// Expected O(log n) per split/merge; traversal is O(n).
// Pitfalls: use random priorities; push before descent and pull afterward.
// Example: pitem t=nullptr; merge(t,t,new item(42,rng64()));
typedef struct item * pitem;
struct item {
    uint64_t prior;
    long long value;
    int cnt = 1;
    bool rev = false;
    pitem l = nullptr, r = nullptr;
    item(long long value, uint64_t prior) : prior(prior), value(value) {}
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int k) {
    if (!t) { l = r = nullptr; return; }
    push (t);
    int left = cnt(t->l);
    if (k <= left)
        split (t->l, l, t->l, k), r = t;
    else
        split (t->r, t->r, r, k-left-1), l = t;
    upd_cnt (t);
}

void reverse (pitem& t, int l, int r) {
    if (l >= r) return;
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void output (pitem t) {
    if (!t)  return;
    push (t);
    output (t->l);
    cout << t->value << ' ';
    output (t->r);
}
