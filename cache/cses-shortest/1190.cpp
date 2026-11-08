#import <bits/stdc++.h>
 
using namespace std;
#define A [a]
#define B [b]

const int c='   ';
 
long n, q, f[c], p[c], s[c], v[c], a, i, e, o, b, j;
 
void u() {
    cin >> e,
    a=i-1|1<<18;
    f A=e, p A=s A=v A=max(e, o);
    while (a>>=1)
        b=j=2*a,
        f A=f B+f[++j],
        p A=max(p B, f B+p[j]),
        s A=max(s[j], f[j]+s B),
        v A=max({v B, v[j], s B+p[j]});
 
}
main()
{
    cin >> n >> q;
 
    while (++i<=n)
        u();
 
    while (q--)
        cin >> i,
        u(),
        cout << v[1] << " ";
}