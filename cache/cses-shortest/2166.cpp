#include <iostream>
using namespace std;
 
int n, l, r, i;
 
struct N {
    long p, s;
    N operator+(N a) 
    { return {max(p, s + a.p), s + a.s}; }
} T[1 << 19], a, b;
 
void M() { for (T[i = l + n] = *T + N{r, r}; i /= 2; T[i] = T[i * 2] + T[i * 2 + 1]); }
 
main() {
    for (cin >> n >> i; l++ < n; )
        cin >> r,
        M();
    for (; cin >> i >> l >> r; (i & 1 ? M : []{
            for (l += n, r += n, a = b = {}; l <= r; l /= 2, r /= 2)
                a = a + T[l & 1 ? l++ : 0], b = T[r & 1 ? 0 : r--] + b;
            cout << (a + b).p << '\n';
        })());
}