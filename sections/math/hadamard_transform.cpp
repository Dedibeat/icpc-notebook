// XOR Fast Walsh-Hadamard Transform.
// n must be a power of two. Use inverse=true after pointwise multiply.
// For modular T, replace division by n with multiplication by inv(n).
// AND/OR convolutions: use superset/subset zeta+mobius (zeta_and_mobius.cpp).
// Time: O(n log n).
template<class T>
void fwht(vector<T>& a, bool inverse = false) {
    int n = (int)a.size();
    for (int len = 1; 2 * len <= n; len <<= 1)
        for (int i = 0; i < n; i += 2 * len)
            for (int j = i; j < i + len; j++) {
                T u = a[j], v = a[j + len];
                a[j] = u + v, a[j + len] = u - v;
            }
    if (inverse) for (T& x : a) x /= n;
}

template<class T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
    fwht(a);
    fwht(b);
    for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
    fwht(a, true);
    return a;
}
