#include <bits/stdc++.h>
using namespace std;
#define D long double
#define Q front()
#define J back()
 
struct L {
    D m, b, l, r;
};
 
int main() {
    D I = 2e15, x, p, f;
    int n, i;
    cin >> n >> x;
    vector<D> s(n);
    for (i=0; i<n; i++) cin >> s[i];
    deque<L> l;
    l.push_back({x, 0, -I, I});
    for (i=0; i<n; i++) {
        cin >> f;
        L F = l.Q;
        while (s[i] > F.r) {
            l.pop_front();
            F = l.Q;
            l.Q.l = -I;
        }
        p = F.m*s[i] + F.b;
        L b = l.J;
        while (b.l*f+p <= b.l*b.m+b.b) {
            l.pop_back();
            b = l.J;
        }
        D s = (p-b.b)/(b.m-f);
        l.J.r = s;
        l.push_back({f, p, s, I});
        if (i == n-1) cout << (long long)p;
    }
}