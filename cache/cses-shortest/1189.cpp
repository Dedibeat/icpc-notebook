#include <bits/stdc++.h>
using namespace std;

#define F for (i = 0; i < n; i++) 
long n, s, v ['   '], u ['   '], i, t;

main () {
    cin >> n;
    F cin >> v[i];
    F cin >> u[i];
    F s += v[i] - u[i], v[i] = s;
    sort(v, v + n);
    s = v[n/2];
    F t += abs(s - v[i]);
    cout << t;
}
