#import <bits/stdc++.h>
using namespace std;

#define J T[P][c]
#define F for (int c : S)
#define E(x) for (; P && x; P = K[P])

int L['   '], K['   '], T['   '][26], Z = 1, P, N, C, R = 1, H['   '], D['   '];

main() {
    string S;
    cin >> S >> *L;
    F {
        c -= 97;
        Z++, P = R, L[Z] = L[P] + 1, R = Z, H[Z]++;
        E (!J) J = Z;
        N = J;
        if (!P)
            K[Z] = 1;
        else if (L[N] == L[P] + 1)
            K[Z] = N;
        else {
            K[Z] = C = Z + 1;
            L[C] = L[P] + 1;
            K[C] = K[N];
            memcpy (T[C], T[N], 104);
            E (J == N) J = C;
            K[N] = ++Z;
        }
    }

    iota (D, D + Z, 1);
    sort (D, D + Z, [] (int a, int b) {
        return L[a] > L[b];
    });
    for (int z : D)
        H[K[z]] += H[z];

    while ( (*L)--) {
        cin >> S;
        P = 1;
        F c -= 97, P = J;
        cout << H[P] << ' ';
    }
}
