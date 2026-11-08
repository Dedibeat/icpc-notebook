#import <bits/stdc++.h>
using namespace std;
set<array<long, 3>> E;
long a, b, c, n, s, D['   '];
int F(long& x) {
    return x = D[x] ? F(D[x]) : x;
}
main()
{
    for (cin >> n >> a;cin >> a >> b >> c;)E.insert({ c,a,b });
    for (auto [x, y, z] : E)
        F(y) - F(z) ? D[y] = z, n--, s += x : 0;
    n - 1 ? cout << "IMPOSSIBLE" : cout << s;
}