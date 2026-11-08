#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<array<int, 3>> rs(n);
    int o = 0;
    for(auto& [l, r, i] : rs)
    {
        cin >> l >> r;
        r = -r;
        i = o++;
    }
    sort(rs.begin(), rs.end());

    vector<int> a1(n), a2(n);
    o = 0;
    for(auto [l, r, i] : rs)
    {
        a2[i] = o >= (r = -r);
        o = max(r, o);
    }
    o = 2e9;
    for(int j = n-1; j >= 0; j--)
    {
        auto [l, r, i] = rs[j];
        a1[i] = o <= (r = -r);
        o = min(r, o);
    }

    for(auto& a : {a1, a2})
    {
        for(int k : a)
            cout << k << ' ';
        cout << '\n';
    }
}

