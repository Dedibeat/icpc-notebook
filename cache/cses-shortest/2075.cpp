#import <bits/stdc++.h>
using namespace std;
const int B = 512;
const int N = 2e6;

int x[N], y[N], w[N], m = 0;
struct {
	int L, R, RB;
} s[B + 1];

void fix(int cn) {
	for (int i = 0, k = 1; i < m; i++)
		if (s[i].RB == 0) {
			for (int j = s[i].L; j <= s[i].R; j++)
				y[k++] = x[j];
		}
		else {
			for (int j = s[i].R; j >= s[i].L; j--)
				y[k++] = x[j];
		}
	for (int i = 1; i <= cn; i++) {
		x[i] = y[i];
		w[x[i]] = i;
	}
	m = 0;
	s[m].L = 1, s[m].R = cn, s[m].RB = 0, m++;
}

int main() {

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		w[x[i]] = i;
	}
	s[m].L = 1, s[m].R = n, s[m].RB = 0, m++;
	cout << n - 1 << "\n";
	for (int i = n; i > 1; i--) {
		if (m >= B)
			fix(i);
		int k = 0, b = 0;
		for (k = m - 1; k >= 0; k--) {
			if (s[k].L <= w[i] && w[i] <= s[k].R)
				break;
			b += s[k].R - s[k].L + 1;
			s[k].RB ^= 1;
		}
		if (s[k].RB == 0) {
			b += s[k].R - w[i] + 1;
			s[m].L = w[i] + 1, s[m].R = s[k].R, s[m].RB = 1, m++;
			s[k].R = w[i] - 1;
		}
		else {
			b += w[i] - s[k].L + 1;
			s[m].L = s[k].L, s[m].R = w[i] - 1, s[m].RB = 0, m++;
			s[k].L = w[i] + 1;
		}
		cout << i - b + 1 << " " << i << "\n";
		for (int l = k + 1, r = m - 2; l < r; l++, r--)
			swap(s[l], s[r]);
	}
	return 0;
}