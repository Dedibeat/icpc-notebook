#import <iostream>
 
long p['   '],n,i,j,m,s,M = 1e9 + 7,d['   '], h['   '];
main() {
    for (std::cin>>n;std::cin>>j;) ++h[j];
    for (*p = 1; i<n;) p[i] = 2 * p[i++] % M;
    for (;i;m=s=0) {
        for (j = i; j<=n; j += i) s += h[j], m += d[j];
        d[i--] = (p[s] +~m%M + M) % M;
    }
    for (;i<n;) printf("%d ",d[++i]);
}