#import <cstdio>
int C[99], n, m, c, p;

main() {
    for (; (c=getchar())>' '; ++n)
        m = ++C[c]>m ? C[c] : m;

    if (2*m > n+1) return! ~puts("-1");

    for (++n; --n; ) for (c = 64; ++c < 91; )
        if (C[c] && c^p && (C[c] == m || n >= 2*m)) {
            putchar(c); --C[p=c]; m = 0;
            for (int x : C) m = x>m ? x : m;
            break;
        }
}
