#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, q, x[N], seg[2 * N];
map<int, set<int>> pos;

void upd(int i, int v) {
    for (seg[i += n] = v; i > 1; i >>= 1) seg[i >> 1] = max(seg[i], seg[i ^ 1]);
}

int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, seg[l++]);
        if (r & 1) res = max(res, seg[--r]);
    }
    return res;
}

void fix(set<int> &s, set<int>::iterator it) {
    if (it == s.end()) return;
    upd(*it - 1, it == s.begin() ? 0 : *prev(it));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pos[x[i]].insert(i);
    }
    for (auto &[v, s] : pos)
        for (auto it = s.begin(); it != s.end(); it++) fix(s, it);

    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            if (x[a] == b) continue;
            set<int> &s = pos[x[a]];
            auto it = s.erase(s.find(a));
            fix(s, it);
            x[a] = b;
            set<int> &s2 = pos[b];
            it = s2.insert(a).first;
            fix(s2, it);
            fix(s2, next(it));
        } else {
            cout << (query(a - 1, b) < a ? "YES" : "NO") << "\n";
        }
    }
}
