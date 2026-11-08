#include <iostream>
using namespace std;
int T[1 << 19], i, l, r, A, n;

void M() {
    for (T[i = l + n] = r; i /= 2; T[i] = min(T[i * 2], T[i * 2 + 1]));
}

void Q() {
    for (l += n, r += n, A = *T; l < r; l /= 2, r /= 2)
        A = min(A, min(T[l & 1 ? l++ : 0], T[r & 1 ? --r : 0]));
    cout << A << '\n';
}

main() {
    T[0] = 2e9;
    for (cin >> n >> A; l < n; l++) cin >> r, M();
    for (; cin >> i >> l >> r; (i & 1 ? M : Q)()) --l;
}