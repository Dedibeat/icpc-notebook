#include <bits/stdc++.h>
#define I long long
#define V vector<
#define M V V I>>
using namespace std;

I m = 3e18, n, i, j, k, a, b, c;

M x (M a, M b) {
	M r (n, V I>(n, m));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				r[i][j] = min(r[i][j], a[i][k] + b[k][j]);
	return r;
}

I f (M b, I e) {
	M r (n, V I>(n, m));

	for (i = 0; i < n; i++)
		r[i][i] = 0;

	while (e) {
		if (e % 2) r = x(r, b);
		b = x(b, b);
		e /= 2;
	}

	return r[0][n-1];
}

int main () {
	cin >> n >> i >> j;
	M r (n, V I>(n, m));

	while (i--) {
		std::cin >> a >> b >> c;
		r[a-1][b-1] = min(c, r[a-1][b-1]);
	}
	a = f(r, j);
	cout << (a == m ? -1 : a);
}

