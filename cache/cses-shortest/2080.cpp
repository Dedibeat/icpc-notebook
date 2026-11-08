#import <bits/stdc++.h>
using namespace std;

#define I long
I n, k, x, y, a;
set<I> G['   '];

map<I, I> D(I u, I p=1, I d = 0) {
    map<I, I> C; C[d] = 1;

    for (I v : G[u])
        if (v != p) {
            auto r = D(v, u, d+1);
            if (r.size() > C.size()) swap(r, C);

            for (auto [x,c] : r) a += c * C[k-x+2*d];
            for (auto [x,c] : r) C[x] += c;
        }

    return C;
}

main() {
    for (cin >> n >> k; cin >> x >> y; G[y].insert(x)) G[x].insert(y);

    D(1);
    cout << a;
}