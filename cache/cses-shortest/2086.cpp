#import <iostream>
#define F(j,b) ;for(j=0;j<b;)
#define c std::cin>>
#define M [3001],
ulong n, k, i, j, a, b = ~0, m, s, x M d M p M f;
 
main() {
    c n >> k
 
    F(i, n) 
        c s, 
        x[++i]=a+=s

 
    F(a, b) {
        m = a + b >> 1 
        F(i, n) {
            d[++i] = ~0
            F(j,i)
                s = x[i] - x[j],
                s = m + d[j] + s * s,
                s < d[i] ? d[i] = s, p[i] = p[j++] + 1 : j++;
        }
        p[n] > k ? a = m + 1 : b = m, f = d[n] - m * k;
    }
 
    std::cout << f;
}
