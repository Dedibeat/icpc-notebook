// Zeta/Mobius transforms. Subset/superset: v.size() must be a power of 2,
// O(n log n). AND-convolution: supersetZeta both, multiply, supersetMobius.
// OR-convolution: subsetZeta both, multiply, subsetMobius.
// Divisor/multiple: v indexed 1..n (v[0] unused), O(n log log n).
// divisorZeta = F(i) = sum_{d|i} f(d);  multipleZeta = F(i) = sum_{i|m} f(m).
// Mobius versions invert their zeta. gcd-convolution: multipleZeta both,
// multiply, multipleMobius (lcm-conv: divisor versions).
template<class T> void subsetZeta(vector<T>& v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1)
        for (int i = 0; i < n; i++) if (i & j) v[i] += v[i ^ j];
}
template<class T> void subsetMobius(vector<T>& v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1)
        for (int i = 0; i < n; i++) if (i & j) v[i] -= v[i ^ j];
}
template<class T> void supersetZeta(vector<T>& v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1)
        for (int i = 0; i < n; i++) if (i & j) v[i ^ j] += v[i];
}
template<class T> void supersetMobius(vector<T>& v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1)
        for (int i = 0; i < n; i++) if (i & j) v[i ^ j] -= v[i];
}
vector<int> primesUpTo(int n) {
    vector<int> pr; vector<bool> comp(n + 1);
    for (int p = 2; p <= n; p++) if (!comp[p]) {
        pr.push_back(p);
        for (int j = 2 * p; j <= n; j += p) comp[j] = true;
    }
    return pr;
}
template<class T> void divisorZeta(vector<T>& v) {
    int n = (int)v.size() - 1;
    for (int p : primesUpTo(n))
        for (int i = 1; i * p <= n; i++) v[i * p] += v[i];
}
template<class T> void divisorMobius(vector<T>& v) {
    int n = (int)v.size() - 1;
    for (int p : primesUpTo(n))
        for (int i = n / p; i; i--) v[i * p] -= v[i];
}
template<class T> void multipleZeta(vector<T>& v) {
    int n = (int)v.size() - 1;
    for (int p : primesUpTo(n))
        for (int i = n / p; i; i--) v[i] += v[i * p];
}
template<class T> void multipleMobius(vector<T>& v) {
    int n = (int)v.size() - 1;
    for (int p : primesUpTo(n))
        for (int i = 1; i * p <= n; i++) v[i] -= v[i * p];
}
