#include <bits/stdc++.h>

using namespace std;
const int c=5001, k=675, mod=1e9+7;
bool pr[c];
int sor[c], cnt, si, n, ans=1, ert[c];
bitset<k> b[k];
int main()
{
    for (int i=2; i<c; i++) {
        if (!pr[i]) {
            sor[++cnt]=i;
            for (int j=i; j<c; j+=i) {
                pr[j]=i;
            }
        }
    }
    cin >> n;
    while (n--) {
        si++;
        int x;
        cin >> x;
        for (int i=1; i<=cnt; i++) {
            while (x%(sor[i]*sor[i])==0) {
                x/=sor[i]*sor[i];
            }
            if (x%sor[i]==0) {
                b[si][i]=1;
            }
        }
        for (int j=1; j<si; j++) {
            if (b[si][ert[j]]) {
                b[si]^=b[j];
            }
        }
        for (int i=k-1; i>=0; i--) {
            if (b[si][i]) {
                ert[si]=i;
            }
        }
        if (!ert[si]) {
            si--;
            ans=2*ans%mod;
        }
    }
    cout << ans << "\n";
    return 0;
}
