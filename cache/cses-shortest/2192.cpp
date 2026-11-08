#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    complex<int64_t> P[n + 1], Q;
    int64_t x, y;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        P[i] = {x, y};
    }
    P[n] = P[0];
    for(int j = 0; j < m; j++) {
        cin >> x >> y;
        Q = {x, y};
        bool b = 0;
        double a = 0;
        for(int i = 0; i < n; i++) {
            auto C = (Q - P[i + 1]) * conj(Q - P[i]);
            b |= abs(imag(C)) == 0 && real(C) <= 0;
            a += arg(complex<double>{real(C), imag(C)});
        }
        cout << (b ? "BOUNDARY" : abs(a) < 1 ? "OUTSIDE" : "INSIDE") << "\n";
    }
}
