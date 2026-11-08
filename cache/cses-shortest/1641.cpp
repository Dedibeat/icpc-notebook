#import <bits/stdc++.h>
using namespace std;
map<int, int> m;
int x, a['  '], i, j;
main() {
    for (cin >> x >> x;cin >> a[++i];);
    for (; --i ; m[a[i]] = i)
        for (j = i; --j ;)
            m.count(x - a[i] - a[j]) && (cout << m[x - a[i] - a[j]] << ' ' << i << ' ' << j,x=0);
    x && cout << "IMPOSSIBLE";
}
