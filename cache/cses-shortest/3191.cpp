#import <bits/stdc++.h>
using namespace std;

int n, m, r, k, v['   '];
main() {
    for (cin >> n; cin >> v[k++];);

    for (; m = *max_element(v, v + n); r = max(r, r ^ m))
        for (int& i : v) i = min(i, i ^ m);
    cout << r;
}