#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;
int N = 1e6+1;

void upd(vi& T, int i, int v) {
    for (; i < N; i += i&-i) {
        T[i] = min(T[i], v);
    }
}

int Q(vi& T, int i) {
    int a = T[i];
    for (; i; i -= i&-i) {
        a = min(a, T[i]);
    }
    return a;
}

main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, i, j, x, y;
    cin >> n >> m;
    array<int, 3> A[n + m];
    for (i = 0; i < n + m; ++i) {
        cin >> x >> y;
        A[i] = {x, y, i};
    }
    sort(A, A + n + m);
    vector<int> R(m, 2*N);
    for (j = -1; j < 2; j += 2) {
        int l = 0;
        vi U(N, 4*N), D(N, 4*N);
        for (auto [x, y, i] : A) {
            if (i < n) {
                l++;
                upd(U, N - y, j*x + y);
                upd(D, y, j*x - y);
            } else {
                R[i - n] = min({R[i - n], -j*x - y + Q(U, N - y), -j*x + y + Q(D, y)});
            }
        }
        reverse(A, A + n + m);
    }

    for (int a : R) cout << a << ' ';
}
