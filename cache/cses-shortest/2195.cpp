#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define N e.size()
#define D e.pop_back();
#define G while(N > l && !r(e[N - 2], e[N - 1], v[i])) D
#define L int64_t
#define p  pair<L, L>

bool r(p a, p b, p c) {
    return a.f*(b.s - c.s) - a.s*(b.f - c.f) + b.f*c.s - b.s*c.f <= 0;
}

L n, i,l=1;

int main() {
    cin >> n;
    vector<p> e, v(n);
    for (p &k : v) cin >> k.f >> k.s;
    for (sort(v.begin(), v.end()); i < n; e.push_back(v[i++])) G l = N;
    for (i -= 2; i + 1; e.push_back(v[i--])) G D cout << N << '\n';
    for (p k : e) cout << k.f << ' ' << k.s << '\n';
}