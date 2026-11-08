#import"bits/stdc++.h"
using namespace std;
long a, b, A['   '], i, l, r, S=1e18;
main () {
	cin >> a >> a >> b;
	for (multiset M{l};cin >> A[++i];S=i<a?S:min(S,*M.begin()-A[i]))
		A[i] += A[i-1],
		M.insert(i>a?A[++r]:S),
		M.extract(i>b? A[l++] : 9);
	cout << -S;
}
