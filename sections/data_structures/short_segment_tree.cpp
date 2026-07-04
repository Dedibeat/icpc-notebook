// Iterative segment tree: point set, range query [l, r). O(log n) per op.
// EDIT ONLY op() and ID. Op must be associative AND commutative
// (sum/min/max/gcd/xor ok; non-commutative like matrix mult needs a
// two-sided query variant).
const int N = 1e5;  // limit for array size
int n;  // array size
long long t[2 * N];

long long op(long long a, long long b) { return a + b; }
const long long ID = 0; // identity: op(x, ID) == x

void build() {  // set t[n..n+i] = a[i] first
  for (int i = n - 1; i > 0; --i) t[i] = op(t[i<<1], t[i<<1|1]);
}

void modify(int p, long long value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = op(t[p], t[p^1]);
}

long long query(int l, int r) {  // op over [l, r)
  long long res = ID;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = op(res, t[l++]);
    if (r&1) res = op(res, t[--r]);
  }
  return res;
}
