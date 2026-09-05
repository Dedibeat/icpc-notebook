### Usage: kth and value count on a subarray

Build `root[i]` for prefix `a[0..i)`. The tree stores compressed ranks, so
decompress the result of `kth`. Both index and value intervals below are
half-open; only `k` is 1-based.

```cpp
// Input: original (uncompressed) values.
vector<long long> a = {4, 1, 4, 2};
vector<long long> xs = a;
sort(xs.begin(), xs.end());
xs.erase(unique(xs.begin(), xs.end()), xs.end());

PST st(xs.size());
vector<int> root(a.size() + 1); // root[0] = empty root 0
for (int i = 0; i < (int)a.size(); ++i) {
    int rank = lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
    root[i + 1] = st.upd(root[i], rank);
}

// Query input: a[l..r)={1,4,2}; k is 1-based.
int l = 1, r = 4, k = 2;
long long kthValue = xs[st.kth(root[l], root[r], k)];

int lo = lower_bound(xs.begin(), xs.end(), 2) - xs.begin();
int hi = lower_bound(xs.begin(), xs.end(), 5) - xs.begin();
int count = st.cnt(root[r], lo, hi) - st.cnt(root[l], lo, hi);
// Expected output: kthValue=2; count=2 values in [2,5).
```

`kth` requires `1 <= k <= r-l`. `upd` needs a rank in `[0,xs.size())`.
The pool grows by `O(log xs.size())` nodes per inserted value.
