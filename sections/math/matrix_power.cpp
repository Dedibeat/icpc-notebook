// Matrix multiply/power mod. mul O(n^3), mpow O(n^3 log e).
// mul needs compatible dimensions; mpow needs a square matrix and e>=0.
// Usage (Fibonacci): mpow({{1,1},{1,0}}, n)[0][1] == F(n).
using ll = long long;
const ll MMOD = 1e9 + 7;
using Mat = vector<vector<ll>>;

Mat mul(const Mat& A, const Mat& B) {
    int n = A.size(), m = B[0].size(), K = B.size();
    Mat C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < K; k++) if (A[i][k])
            for (int j = 0; j < m; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MMOD;
    return C;
}

Mat mpow(Mat A, ll e) {
    int n = A.size();
    Mat R(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    for (; e; e >>= 1, A = mul(A, A))
        if (e & 1) R = mul(R, A);
    return R;
}
