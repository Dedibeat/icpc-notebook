#include <bits/stdc++.h>
using namespace std;
using L = long;
#define V vector
using P = pair<L, int>;

#define A auto
int main() {
    int n, m, a, k, i; cin >> n >> m;
    V<V<P>> g(n + m);
    V<L> c(m), D(n + m, -1);
    for (A &x : c) cin >> x;

    i = n;
    for (A x : c) {
        cin >> k;
#define B push_back
        while (k--)
            cin >> a, g[--a].B({x, i}), g[i].B({0, a});
        i++;
    }

    priority_queue<P> q;
    q.push({0, 0});

    while (q.size()) {
        A [d, u] = q.top();
        q.pop();

        if (D[u] < 0) {
            D[u] = -d;

            for (A [w, v] : g[u]) q.push({d - w, v});
        }
    }

    for (i = 0; i < n;) cout << D[i++] << ' ';
}
