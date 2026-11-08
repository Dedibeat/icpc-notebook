#include <bits/stdc++.h>
using namespace std;
using E = size_t;
using H = array<E, 7>;
E k, s;
#define K(i) vector<H> i(7);
#define p(i) for (E i = 0; i < 6; ++i)
#define Q(a, b) a += b, a %= 1000000007
#define U(A) K(C) p(i) p(j) p(k) Q(C[i][j], A[i][k] * m[k][j]); A = C;
main()
{
    K(m) K(R)
    p(i) m[i][i + 1] = R[i][i] = m[5][i] = 1;
    for (cin >> k, --k; k; k /= 2)
    {
        if (k % 2) {U(R)}
        U(m);
    }
    p(i) Q(s, R[0][i] * (1 + k)), k += 1 + k;
    cout << s;
}
