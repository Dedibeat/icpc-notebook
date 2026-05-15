// XOR Fast Walsh-Hadamard Transform.
// n must be a power of two. Use inverse=true after pointwise multiply.
// For modular T, replace division by n with multiplication by inv(n).
// Time: O(n log n).
template<class T>
void fwht(vector<T>& a, bool inverse = false) {
    int n = (int)a.size();
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                T u = a[i + j], v = a[i + len + j];
                a[i + j] = u + v;
                a[i + len + j] = u - v;
            }
        }
    }
    if (inverse) {
        for (T& x : a) x /= n;
    }
}

template<class T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
    fwht(a);
    fwht(b);
    for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
    fwht(a, true);
    return a;
}
