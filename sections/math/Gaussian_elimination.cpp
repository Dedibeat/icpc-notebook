int gauss(vector<vector<long long>> a, int mod) {
    int n = a.size(), m = a[0].size() - 1;
    int row = 0;

    for (int col = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (a[i][col] % mod != 0) {
                sel = i;
                break;
            }
        }
        if (a[sel][col] % mod == 0) continue;
        swap(a[sel], a[row]);
        long long invp = inv((a[row][col] % mod + mod) % mod, mod);
        for (int j = col; j <= m; j++) a[row][j] = a[row][j] * invp % mod;

        for (int i = 0; i < n; i++) {
            if (i != row && a[i][col]) {
                long long f = a[i][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] = (a[i][j] - f * a[row][j]) % mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
        }
        row++;
    }
    return row; // rank
}