const int N = 1e5;  // limit for array size
int n;  // array size
long long t[2 * N];

void build() {  // build the tree (first set positions n through 2n-1 as original array
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, long long value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

long long query(int l, int r) {  // sum on interval [l, r)
  long long res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
