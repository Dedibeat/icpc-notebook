#import <bits/stdc++.h>
#define W std::cin>>
#define Z S[R][
#define m (l+r)/2
using I = long;
std::array<I, 3> S['   '*8];
I V['   '], C, N, x, y, z, i;
 
void M(I& R, I r = N, I l = 0) {
    S[++C] = S[R];
    R = C;
    Z 2] = y;
    r - l > 1 ?
    M(Z x > m], x > m ? r : m, x > m ? m : l),
    Z 2] = S[Z 0]][2] + S[Z 1]][2] : 0;
}
 
I Q(I R, I l, I r) {
    return r < x | l >= y ? 0 :
    x > l + 1 | r > y ?
    Q(Z 0], l, m) + Q(Z 1], m, r) : Z 2];
}
 
main(I T) {
    for (W N >> y; x++ < N; M(V[1]))
    W y;
    for (; W i >> z;)
        if(i > 2) V[++T] = V[z];
        else if (W x >> y, i < 2) M(V[z]);
        else printf("%ld ", Q(V[z], 0, N));
}