#include <bits/stdc++.h>

using namespace std;

main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, N;
    cin >> n >> m;
    N = min(n, m);
    int A[N], P[N + 1], C[N], i = 0, p, x;
    while (n--) {
        cin >> A[i];
        if (A[i] <= N) { P[A[i]] = i; ++i; }
    }
    vector<int> L, S;
    while (m--) {
        cin >> x;
        if (x <= N) {
            x = P[x];
            p = lower_bound(L.begin(), L.end(), x) - L.begin();
            if (p == L.size()) L.push_back(x);
            else L[p] = x;
            C[x] = (p == 0 ? -1 : L[p - 1]);
        }
    }
    cout << L.size() << "\n";
    for (i = L.back(); i != -1; i = C[i]) S.push_back(A[i]);
    reverse(S.begin(), S.end());
    for (int e : S) {
        cout << e << " ";
    }
}
