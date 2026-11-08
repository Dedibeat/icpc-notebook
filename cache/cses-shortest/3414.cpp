#include <iostream>
using namespace std;
long n, m, l, i, j, k, A[26], H[3001], b[3001], t, B[3001];
#define w(x) for(x = 1; x < n; x ++) {
main() {
    cin>>n>>m; ++n;
    string s, p(n, '.');
    w(i) 
        cin >> s;
        s = "." + s;
        t = l = b[t ++] = 0;
        w(j) 
            H[j] = 1 + (s[j] ^ p[j] ? 0 : H[j]);
            while (H[b[t - 1]] > H[j]) t --;
            if (s[j] ^ s[j - 1]) l = j;
            k = b[t - 1];
            A[s[j] - 65] += B[j] = k < l ? (j - l + 1) * H[j] : (j - k) * H[j] + B[k];
            b[t ++] = j;
        }
        p = s;
    }
    n = m + 1;
    w(i) cout<<A[i - 1]<<' '; }
}
