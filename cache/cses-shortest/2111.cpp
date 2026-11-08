#include <bits/stdc++.h>
using namespace std;
#define V vector
#define R return

int l, k, n, m, p = 19, N = 1<<p, i, x;
 
struct C {
    double r, c;
 
    C operator+ (const C& a) {
        R {r+a.r, c+a.c};
    }
    
    C operator* (const C& a) {
        R {r*a.r-c*a.c, r*a.c+c*a.r};
    }
};
 
V<C> F(V<C>& f, int N, int p) {
    l = f.size();
    if (l == 1) R V<C>(N, f[0]);
    
    V<C> E, D;
    for (i=0; i<l; i++) 
        if (i & 1) D.push_back(f[i]); 
        else E.push_back(f[i]);
    
    V<C> e = F(E, N/2, p-1), d = F(D, N/2, p-1), a(N);
    for (i=0; i<N; i++) {
        double t = 2*M_PI*i/(1<<p);
        a[i] = e[i%(N/2)] + (C){cos(t), sin(t)} * d[i%(N/2)]; 
    }
    R a;
}
 
int main() {
    ios::sync_with_stdio(false);

    cin >> k >> n >> m;
    V<C> f(k+1), B(N), A, C;
    while (n--) {
        cin >> x;
        f[x].r++;
    }
    while (cin >> x) f[x].c++;
    A = F(f, N, p);
    for (i=0; i<N; i++) B[i] = A[i] * A[i];
    
    C = F(B, N, p);
    for (i=2; i<=k*2; i++) cout << (long long)round(C[N-i].c/N/2) << " ";
    
}