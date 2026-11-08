#import <iostream>
using namespace std;

#define M 1<<19
#define F for (int
#define X   [j]
long n, q, a[M], L[M], R[M], G[M], P[M], A[M], S[M][19],x;

main () {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> q;

    F j = 0 ; j < n ; j++)
        cin >> a X ,S[j + 1][0] = a X ;

    F j = 0 ; j < q ; j++)
        cin >> L X  >> R X ,G X  = __lg(R X  - L X  + 1);

    F i = 0 ; i < 31 ; i++) {
        F j = 0 ; j < n ; j++)
            if (P[j + 1] = P X ; a X  < 1 << i)
                P[j + 1] += a X ,S[j + 1][0] = 2e9;
        F j = n ; j > 0 ; j--)
            F k = 1 ; k < 19 ; k++)
                if (S X [k-1] < (S X [k] = S[j + (1 << k - 1)][k - 1])) S X [k] = S X [k-1];
        F j = 0 ; j < q ; j++)
            if (x = P[R X ] - P[L X -1] + 1;(i > 29 || min(S[L X ][G X ],S[R X  -  (1 << G X ) + 1][G X ]) > x) && !A X) A X  = x;
    }
    F i = 0 ; i < q ; )
        cout << A[i++] << ' ';
}
