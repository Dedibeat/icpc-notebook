#import <regex>
#define S scanf("%d",
#define F for (
int D['  ']['  '], a['  '], b['  '], C['  '], i, j, n, m, s;

main() {
    S &n); S &m);
    F ;~S (i<n ? a : b-n) + i++););

    F ; j < m; ++j)
        F i = 0; i < n; ++i)
            D[j+1][i+1] = a[i]^b[j]
                ? std::max(D[j][i+1], D[j+1][i])
                : D[j][i]+1;

    F ;i*j;)
        a[--i] == b[--j]
            ? C[s++] = a[i]
            : D[j][i+1] > D[j+1][i] ? ++i : ++j;

    F C[s] = s; ~s; ) printf("%d ", C[s--]);
}
