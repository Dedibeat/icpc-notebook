#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll M = 1e9 + 7, n, i = 1, l = 0, x, s = 1;

main() {
    cin >> n;

    map<ll, ll> p;
    vector<ll> c(n + 1, 1);
    while (i <= n) {
        cin >> x;
        
        while (l < p[x])
            s -= c[l++];

        c[i] = (s % M + M) % M;

        s *= 2;
        s = (s % M + M) % M;

        p[x] = i++;
    }

    cout << c[n];
}