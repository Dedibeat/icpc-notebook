#import "bits/stdc++.h"

using namespace std;

int A, k;

main () {
    cin >> k >> A;
    bitset <30> g[k], *j;
    for (auto &i: g)
      for (cin >> i, j = g; j < &i;)
        A = min(A, k = (i ^ *j++).count());
    cout << A;
}
