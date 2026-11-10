// Sort cyclic shifts or use suffix_array(s) for all suffixes. O(n log n).
// Bytes are compared unsigned; the optional sentinel is smaller than any byte.
vector<int> sort_cyclic_shifts(const string& s, bool sentinel = false) {
    int n = s.size() + sentinel;
    if (n == 0) return {};
    const int alphabet = 257;
    auto code = [&](int i) { return i == (int)s.size() ? 0 : 1 + (unsigned char)s[i]; };
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[code(i)]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++) p[--cnt[code(i)]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (code(p[i]) != code(p[i-1])) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n && classes < n; ++h) { // stop once all distinct
        for (int i = 0; i < n; i++) pn[i] = (p[i] - (1 << h) + n) % n;
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

// sa[i] = start of i-th smallest suffix. Use with lcp_array (Kasai) from lcp.cpp.
vector<int> suffix_array(const string& s) {
    vector<int> p = sort_cyclic_shifts(s, true);
    return vector<int>(p.begin() + 1, p.end());
}
