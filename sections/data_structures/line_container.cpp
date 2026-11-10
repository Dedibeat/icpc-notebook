// CHT: add lines y = k*x + m, query MAXIMUM at x. Amortized O(log n) per op.
// For MINIMUM: add(-k, -m) and use -get(x).
// Keeps the notebook's #define int long long convention.
// Breakpoints and evaluations use __int128; coefficients/x are signed 64-bit.
// get returns __int128: do not narrow unless the result fits long long.
// MIN via negation requires k,m != LLONG_MIN (negating them would overflow).
// add(k,m) inserts y=kx+m; get(x) returns the largest inserted line value.
// Example: add(2,1); add(-1,7); get(3)==7. get needs a nonempty container.
#define int long long
struct Line {
	int k, m;
	mutable __int128 p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(int x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	static constexpr __int128 inf = (__int128)1 << 126;
	__int128 div(__int128 a, __int128 b) { // floored division
		return a / b - ((a < 0) != (b < 0) && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div((__int128)y->m - x->m, (__int128)x->k - y->k);
		return x->p >= y->p;
	}
	void add(int k, int m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	__int128 get(int x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (__int128)l.k * x + l.m;
	}
};
