#include <bits/stdc++.h>

int main() {
    using namespace std;

    int n, q, l, r, i;
    cin >> n >> q;
    vector<int> h(n), o(q), s;
    for (int &x : h)
        cin >> x;
    vector<vector<array<int, 2>>> Q(n);
    for (i = 0; i < q; ++i) {
        cin >> l >> r;
        Q[l - 1].push_back({i, r - 1});
    }

    for (i = n - 1; i >= 0; --i) {
        while (!s.empty() && h[s.back()] <= h[i])
            s.pop_back();
        s.push_back(i);
        for (auto [j, r] : Q[i])
            o[j] = std::upper_bound(s.rbegin(), s.rend(), r) - s.rbegin();
    }
    for (int x : o)
        cout << x << "\n";
}
