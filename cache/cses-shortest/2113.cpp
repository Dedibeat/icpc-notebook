#include <bits/stdc++.h>
using namespace std;

#define Q int
#define x complex<double>
#define F(l) for (Q j = 0; j < l; j++)
#define E(x) * p] = T[j * p * 2] + x * w * T[p + j * p * 2],
#define X 1 << 19
#define Y(r) f(r, o, p * 2, q / 2);

x A[X], B[X], T[X];
Q n, m;

void f(x *r, Q o, Q p=1, Q q=X) {
    if (q - 1) {
        x W = exp(x(0, o * M_PI / q));
        Y(r)
        Y(r + p)

        F(q) T[j * p] = r[j * p];

        x w = 1;
        F(q / 2)
            r[j E(1.)
            r[(j + q / 2) E(-1.)
            w *= W;
    }
}

main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;

    F(n) cin >> A[j];
    while (m--) cin >> B[m], n++;

    f(A, 2);
    f(B, 2);

    F(X) A[j] *= B[j];
    f(A, -2);

    F(n - 1) cout << Q(A[j].real() / (X) + .5) << ' ';
}
