#include <bits/stdc++.h>
using namespace std;
#define E return
#define I int
#define M max

struct o {
    long long x, l, r, a;
};
 
o m(o x, o y) {
    E {M(M(x.x, y.x), x.r+y.l), M(x.l, x.a+y.l), M(y.r, y.a+x.r), x.a+y.a};
}
 
I n, q, L, R, N=1;
o a[900000];
 
o g(I D, I l, I r) {
    if (L <= l && r <= R) E a[D];
    
    if (L >= r || l >= R) E {};
    
    I d = (l + r) / 2;
    
    E m(g(D*2, l, d), g(D*2+1, d, r));
}
 
I main() {
    cin >> n >> q;
    
    while (N<n) N*=2;
    I A = N;
    
    for (L=0; L<n; L++) {
        cin >> R;
        I Q = M(R, 0);
        a[N+L] = {Q, Q, Q, R};
    }
    
    for (; N; N>>=1) for (L=N; L<N*2; L+=2) a[L/2] = m(a[L], a[L+1]);
    
    while (q--) {
        cin >> L >> R;
        L--;
        cout << g(1, 0, A).x << "\n";
    }
}