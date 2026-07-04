// Solve A x = b mod PRIME p. a = n rows of m+1 entries (last column is b).
// Returns -1 if no solution, else the number of FREE variables (0 = unique).
// sol gets one valid solution (free variables set to 0). O(n m min(n,m)).
// Rank of A alone: pass b = 0 column; rank = m - free. Self-contained.
long long gpow(long long a, long long e, long long mod) {
    long long r = 1;
    for (a %= mod; e; e >>= 1, a = a * a % mod)
        if (e & 1) r = r * a % mod;
    return r;
}

int gauss(vector<vector<long long>> a, long long mod, vector<long long>& sol) {
    int n = a.size(), m = (int)a[0].size() - 1, row = 0;
    for (auto& r : a) for (auto& x : r) x = (x % mod + mod) % mod;
    vector<int> where(m, -1);
    for (int col = 0; col < m && row < n; col++) {
        int sel = row;
        while (sel < n && !a[sel][col]) sel++;
        if (sel == n) continue;
        swap(a[sel], a[row]);
        long long invp = gpow(a[row][col], mod - 2, mod);
        for (int j = col; j <= m; j++) a[row][j] = a[row][j] * invp % mod;
        for (int i = 0; i < n; i++) if (i != row && a[i][col]) {
            long long f = a[i][col];
            for (int j = col; j <= m; j++)
                a[i][j] = ((a[i][j] - f * a[row][j]) % mod + mod) % mod;
        }
        where[col] = row++;
    }
    for (int i = row; i < n; i++) // leftover rows are all-zero except maybe b
        if (a[i][m]) return -1;
    sol.assign(m, 0);
    for (int c = 0; c < m; c++)
        if (where[c] != -1) sol[c] = a[where[c]][m];
    return m - row; // row = rank
}
