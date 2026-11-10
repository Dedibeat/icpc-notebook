// Brute-force checks for every formula in sections/math/counting_formulas.md.
// The two printed functions are compiled from the .md by test_notebook_examples.py.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll P = 1000000007;

ll pw(ll a, ll e, ll m) { ll r = 1 % m; a %= m; for (; e; e >>= 1, a = a * a % m) if (e & 1) r = r * a % m; return r; }
ll phi(ll m) { ll r = m; for (ll p = 2; p * p <= m; p++) if (m % p == 0) { while (m % p == 0) m /= p; r -= r / p; } if (m > 1) r -= r / m; return r; }

int main() {
    // Floor blocks: blocks partition [1,n], floor(n/i) is constant inside and changes between.
    for (ll n = 1; n <= 3000; n++) {
        ll blocks = 0, last = -1;
        for (ll l = 1, r; l <= n; l = r + 1) {
            ll q = n / l; r = n / q; ++blocks;
            assert(l <= r && r <= n && q != last && n / r == q && (r == n || n / (r + 1) != q));
            last = q;
        }
        assert(blocks <= 2 * sqrtl(n) + 1);
    }
    { // sum floor(n/i) = total number of divisors of 1..n
        vector<ll> d(3001);
        for (int x = 1; x <= 3000; x++) for (int k = x; k <= 3000; k += x) d[k]++;
        ll pref = 0;
        for (ll n = 1; n <= 3000; n++) {
            pref += d[n];
            ll s = 0; for (ll i = 1; i <= n; i++) s += n / i;
            assert(s == pref);
        }
    }
    // Two-number blocks: r = min(n/(n/l), m/(m/l)) keeps both quotients constant.
    for (ll n = 1; n <= 120; n++) for (ll m = 1; m <= 120; m++)
        for (ll l = 1, r; l <= min(n, m); l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            for (ll i = l; i <= r; i++) assert(n / i == n / l && m / i == m / l);
            assert(r == min(n, m) || n / (r + 1) != n / l || m / (r + 1) != m / l);
        }

    // Exponent reduction.
    for (ll p : {2LL, 3LL, 5LL, 7LL, 13LL, 1000000007LL})
        for (ll a = 1; a <= 30; a++) if (a % p)
            for (ll e = 0; e <= 60; e++) assert(pw(a, e, p) == pw(a, e % (p - 1), p));
    for (ll m = 1; m <= 80; m++) {
        ll f = phi(m);
        for (ll a = 0; a <= 80; a++) for (ll e = f; e <= f + 200; e++)
            assert(pw(a, e, m) == pw(a, e % f + f, m));
    }
    { // phi chain m, phi(m), ... reaches 1 in O(log m) steps
        const int LIM = 1000000;
        vector<int> ph(LIM + 1); iota(ph.begin(), ph.end(), 0);
        for (int p = 2; p <= LIM; p++) if (ph[p] == p) for (int k = p; k <= LIM; k += p) ph[k] -= ph[k] / p;
        for (int m = 2; m <= LIM; m++) {
            int steps = 0; for (int x = m; x > 1; x = ph[x]) steps++;
            assert(steps <= __lg(m) + 1);
        }
    }
    { // towers a0^(a1^(a2^...)) mod m with "x < m ? x : x % m + m" values, against exact ones
        auto MP = [](ll x, ll m) { return x < m ? x : x % m + m; };
        auto powMP = [&](ll a, ll e, ll m) { ll r = 1; a = MP(a, m); for (; e; e >>= 1, a = MP(a * a, m)) if (e & 1) r = MP(r * a, m); return r; };
        const ll CAP = 1000000000000000LL, BIG = -1;
        function<ll(const vector<ll>&, int)> exact = [&](const vector<ll>& a, int i) -> ll {
            if (i + 1 == (int)a.size()) return a[i];
            ll e = exact(a, i + 1);
            if (a[i] <= 1) return a[i] == 1 || e == 0 ? 1 : 0; // e == BIG means e >= 1
            if (e == BIG || e >= 60) return BIG;
            ll r = 1; for (ll t = 0; t < e; t++) { r *= a[i]; if (r > CAP) return BIG; }
            return r;
        };
        function<ll(const vector<ll>&, int, ll)> tower = [&](const vector<ll>& a, int i, ll m) -> ll {
            if (i + 1 == (int)a.size()) return MP(a[i], m);
            return powMP(a[i], tower(a, i + 1, phi(m)), m);
        };
        int checked = 0;
        for (int len = 1; len <= 4; len++) {
            int total = 1; for (int i = 0; i < len; i++) total *= 6;
            for (int code = 0; code < total; code++) {
                vector<ll> a(len); for (int i = 0, x = code; i < len; i++) a[i] = x % 6, x /= 6;
                ll v = exact(a, 0);
                if (v == BIG) continue;
                for (ll m = 1; m <= 100; m++) assert(tower(a, 0, m) % m == v % m), checked++;
            }
        }
        assert(checked > 50000);
    }

    // Binomial table mod P, plus exact parity table.
    const int N = 300;
    vector<vector<ll>> C(N + 1, vector<ll>(N + 1));
    for (int n = 0; n <= N; n++) { C[n][0] = 1; for (int k = 1; k <= n; k++) C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % P; }
    auto c = [&](int n, int k) -> ll { return k < 0 || k > n || n < 0 ? 0 : C[n][k]; };
    vector<vector<int>> odd(N + 1, vector<int>(N + 1));
    for (int n = 0; n <= N; n++) { odd[n][0] = 1; for (int k = 1; k <= n; k++) odd[n][k] = odd[n - 1][k - 1] ^ odd[n - 1][k]; }
    for (int n = 0; n <= N; n++) for (int k = 0; k <= n; k++) assert(odd[n][k] == ((k & n) == k));
    mt19937 rng(9);
    for (int it = 0; it < 300; it++) { // XOR pyramid top
        int n = 1 + rng() % 40;
        vector<ll> a(n); for (auto& x : a) x = rng() % 1000;
        ll want = 0; for (int i = 0; i < n; i++) if ((i & (n - 1)) == i) want ^= a[i];
        auto row = a;
        while (row.size() > 1) { vector<ll> nx(row.size() - 1); for (size_t i = 0; i + 1 < row.size(); i++) nx[i] = row[i] ^ row[i + 1]; row = nx; }
        assert(row[0] == want);
    }
    for (int a = 0; a <= 60; a++) for (int b = 0; b <= 60; b++) for (int k = 0; k <= a + b; k++) { // Vandermonde
        ll s = 0; for (int i = 0; i <= k; i++) s = (s + c(a, i) * c(b, k - i)) % P;
        assert(s == c(a + b, k));
    }
    for (int n = 0; 2 * n <= N; n++) { // sum of squares
        ll s = 0; for (int i = 0; i <= n; i++) s = (s + c(n, i) * c(n, i)) % P;
        assert(s == c(2 * n, n));
    }
    for (int r = 0; r <= 100; r++) for (int n = r; n < N; n++) { // hockey stick
        ll s = 0; for (int i = r; i <= n; i++) s = (s + c(i, r)) % P;
        assert(s == c(n + 1, r + 1));
    }
    for (ll n = 0; n < N; n++) assert(n * (n + 1) / 2 % P == c(n + 1, 2));
    for (int k = 1; k <= 5; k++) for (int n = 0; n <= 10; n++) { // stars and bars
        ll ge0 = 0, ge1 = 0;
        vector<int> x(k);
        function<void(int, int)> go = [&](int i, int left) {
            if (i == k - 1) { x[i] = left; ge0++; ge1 += *min_element(x.begin(), x.end()) >= 1; return; }
            for (int v = 0; v <= left; v++) x[i] = v, go(i + 1, left - v);
        };
        go(0, n);
        assert(ge0 == c(n + k - 1, k - 1) && ge1 == (n >= 1 ? c(n - 1, k - 1) : 0));
    }
    for (int k = 1; k <= 4; k++) for (int u = 0; u <= 5; u++) for (int n = 0; n <= 14; n++) { // x_i <= u
        ll brute = 0, total = 1;
        for (int i = 0; i < k; i++) total *= u + 1;
        for (ll code = 0; code < total; code++) {
            ll x = code, s = 0; for (int i = 0; i < k; i++) s += x % (u + 1), x /= u + 1;
            brute += s == n;
        }
        ll f = 0;
        for (int j = 0; n - j * (u + 1) >= 0; j++) f += (j % 2 ? -1 : 1) * c(k, j) * c(n - j * (u + 1) + k - 1, k - 1);
        assert(brute == f);
    }
    for (int L = 0; L <= 18; L++) for (int h = 0; h <= 20; h++) { // reflection
        ll brute = 0;
        for (int mask = 0; mask < (1 << L); mask++) {
            int cur = h; bool ok = true;
            for (int i = 0; i < L && ok; i++) cur += mask >> i & 1 ? 1 : -1, ok = cur >= 0;
            brute += ok && cur == 0;
        }
        ll f = (L - h) % 2 || L < h ? 0 : c(L, (L - h) / 2) - c(L, (L - h) / 2 - 1);
        assert(brute == f);
    }
    for (int n = 0; n <= 15; n++) // h = 0, L = 2n gives Catalan (values stay below P here)
        assert(c(2 * n, n) - c(2 * n, n - 1) == c(2 * n, n) / (n + 1) && c(2 * n, n) % (n + 1) == 0);

    // Number families against brute force.
    const int M = 9;
    vector<vector<ll>> S(M + 1, vector<ll>(M + 1)), c1 = S, A = S;
    S[0][0] = c1[0][0] = 1; A[1][0] = 1;
    for (int n = 1; n <= M; n++) for (int k = 1; k <= n; k++) {
        S[n][k] = k * S[n - 1][k] + S[n - 1][k - 1];
        c1[n][k] = (n - 1) * c1[n - 1][k] + c1[n - 1][k - 1];
    }
    for (int n = 2; n <= M; n++) for (int k = 0; k < n; k++)
        A[n][k] = (k + 1) * A[n - 1][k] + (k ? (n - k) * A[n - 1][k - 1] : 0);
    vector<ll> Bell;
    for (int n = 0; n <= M; n++) { // set partitions via restricted growth strings
        vector<ll> cnt(n + 1);
        vector<int> g(n);
        function<void(int, int)> go = [&](int i, int mx) {
            if (i == n) { cnt[mx]++; return; }
            for (int v = 0; v <= mx; v++) g[i] = v, go(i + 1, max(mx, v + 1));
        };
        go(0, 0);
        ll bell = 0;
        for (int k = 0; k <= n; k++) {
            assert(cnt[k] == S[n][k]);
            ll fact = 1, ex = 0; for (int i = 2; i <= k; i++) fact *= i;
            for (int i = 0; i <= k; i++) ex += (i % 2 ? -1 : 1) * c(k, i) * (ll)pow(k - i, n);
            assert(ex == fact * S[n][k]);
            bell += S[n][k];
        }
        Bell.push_back(bell);
        if (n >= 1) { ll s = 0; for (int k = 0; k < n; k++) s += c(n - 1, k) * Bell[k]; assert(s == bell); }
    }
    assert((vector<ll>(Bell.begin(), Bell.begin() + 9) == vector<ll>{1, 1, 2, 5, 15, 52, 203, 877, 4140}));
    for (int n = 1; n <= M; n++) assert(S[n][0] == 0);
    assert((vector<ll>{S[4][1], S[4][2], S[4][3], S[4][4]} == vector<ll>{1, 7, 6, 1}));
    assert((vector<ll>{c1[4][1], c1[4][2], c1[4][3], c1[4][4]} == vector<ll>{6, 11, 6, 1}));
    assert((vector<ll>{A[3][0], A[3][1], A[3][2]} == vector<ll>{1, 4, 1}));
    assert((vector<ll>{A[4][0], A[4][1], A[4][2], A[4][3]} == vector<ll>{1, 11, 11, 1}));
    for (int n = 0; n <= 7; n++) for (int k = 0; k <= 5; k++) { // onto maps = k! S(n,k)
        ll total = 1, onto = 0, fact = 1;
        for (int i = 0; i < n; i++) total *= k;
        for (int i = 2; i <= k; i++) fact *= i;
        for (ll code = 0; code < total; code++) {
            int hit = 0; ll x = code; for (int i = 0; i < n; i++) hit |= 1 << (x % k), x /= k;
            onto += hit == (1 << k) - 1;
        }
        assert(onto == fact * S[n][k]);
    }
    for (int n = 0; n <= M; n++) { // rising factorial x(x+1)...(x+n-1) has coefficients c(n,k)
        vector<ll> poly{1};
        for (int i = 0; i < n; i++) { // multiply by (x + i)
            vector<ll> nx(poly.size() + 1);
            for (size_t j = 0; j < poly.size(); j++) nx[j + 1] += poly[j], nx[j] += i * poly[j];
            poly = nx;
        }
        ll fact = 1, sum = 0; for (int i = 2; i <= n; i++) fact *= i;
        for (int k = 0; k <= n; k++) assert(poly[k] == c1[n][k]), sum += c1[n][k];
        assert(sum == fact);
    }
    vector<ll> D = {1, 0};
    for (int n = 2; n <= M; n++) D.push_back((n - 1) * (D[n - 1] + D[n - 2]));
    for (int n = 1; n <= M; n++) assert(D[n] == n * D[n - 1] + (n % 2 ? -1 : 1));
    assert((vector<ll>(D.begin(), D.begin() + 8) == vector<ll>{1, 0, 1, 2, 9, 44, 265, 1854}));
    for (int n = 1; n <= 6; n++) { // swap distance to identity = n - cycles (BFS)
        vector<int> id(n); iota(id.begin(), id.end(), 0);
        map<vector<int>, int> dist{{id, 0}};
        queue<vector<int>> q; q.push(id);
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
                auto t = p; swap(t[i], t[j]);
                if (!dist.count(t)) dist[t] = dist[p] + 1, q.push(t);
            }
        }
        for (auto& [p, d] : dist) {
            vector<int> seen(n); int k = 0;
            for (int i = 0; i < n; i++) if (!seen[i]) { k++; for (int j = i; !seen[j]; j = p[j]) seen[j] = 1; }
            assert(d == n - k);
        }
    }
    for (int n = 1; n <= 8; n++) { // cycles, descents, derangements, collecting passes
        vector<int> p(n); iota(p.begin(), p.end(), 0);
        vector<ll> cyc(n + 1), des(n), passes(n + 1), fixedCnt(n + 1);
        ll der = 0;
        do {
            vector<int> seen(n); int k = 0;
            for (int i = 0; i < n; i++) if (!seen[i]) { k++; for (int j = i; !seen[j]; j = p[j]) seen[j] = 1; }
            cyc[k]++;
            int d = 0; for (int i = 0; i + 1 < n; i++) d += p[i] > p[i + 1];
            des[d]++;
            int fixedPoints = 0; for (int i = 0; i < n; i++) fixedPoints += p[i] == i;
            der += fixedPoints == 0, fixedCnt[fixedPoints]++;
            vector<int> pos(n); for (int i = 0; i < n; i++) pos[p[i]] = i; // simulate CSES rounds
            int rounds = 0, next = 0;
            while (next < n) { rounds++; for (int i = 0; i < n; i++) if (p[i] == next) next++; }
            int invDesc = 0; for (int x = 0; x + 1 < n; x++) invDesc += pos[x] > pos[x + 1];
            assert(rounds == 1 + invDesc);
            passes[rounds]++;
        } while (next_permutation(p.begin(), p.end()));
        for (int k = 1; k <= n; k++) assert(cyc[k] == c1[n][k]);
        for (int k = 0; k < n; k++) assert(des[k] == A[n][k] && passes[k + 1] == A[n][k]);
        assert(der == D[n]);
        for (int k = 0; k <= n; k++) assert(fixedCnt[k] == c(n, k) * D[n - k]);
    }

    // Prufer code exactly as the sheet describes it.
    auto encode = [](int n, vector<pair<int, int>> edges) {
        vector<set<int>> adj(n);
        for (auto [a, b] : edges) adj[a].insert(b), adj[b].insert(a);
        vector<int> code;
        for (int t = 0; t < n - 2; t++) {
            int leaf = 0; while (adj[leaf].size() != 1) leaf++; // smallest leaf
            int nb = *adj[leaf].begin();
            code.push_back(nb);
            adj[nb].erase(leaf), adj[leaf].clear();
        }
        return code;
    };
    auto decode = [](int n, const vector<int>& code) {
        vector<int> d(n, 1);
        for (int x : code) d[x]++;
        vector<pair<int, int>> edges;
        for (int x : code) {
            int v = 0; while (d[v] != 1) v++; // smallest v with d_v = 1
            edges.push_back({min(v, x), max(v, x)});
            d[v]--, d[x]--;
        }
        int u = -1, w = -1;
        for (int v = 0; v < n; v++) if (d[v] == 1) (u < 0 ? u : w) = v;
        edges.push_back({u, w});
        sort(edges.begin(), edges.end());
        return edges;
    };
    // Cayley, degree formula, rooted forests, Prufer: enumerate edge subsets of K_n.
    for (int n = 1; n <= 7; n++) {
        vector<pair<int, int>> E;
        for (int a = 0; a < n; a++) for (int b = a + 1; b < n; b++) E.push_back({a, b});
        int m = E.size();
        ll trees = 0;
        map<vector<int>, ll> byDeg;
        vector<ll> forests(n + 1);
        vector<int> pick;
        function<void(int)> go = [&](int i) {
            if ((int)pick.size() > n - 1) return;
            if (i == m) {
                vector<int> par(n); iota(par.begin(), par.end(), 0);
                function<int(int)> f = [&](int x) { return par[x] == x ? x : par[x] = f(par[x]); };
                bool acyclic = true; vector<int> deg(n);
                for (int e : pick) {
                    auto [a, b] = E[e]; deg[a]++, deg[b]++;
                    if (f(a) == f(b)) acyclic = false; else par[f(a)] = f(b);
                }
                if (!acyclic) return;
                int k = n - pick.size(); // components
                if (k == 1) {
                    trees++, byDeg[deg]++;
                    if (n >= 2) {
                        vector<pair<int, int>> edges; for (int e : pick) edges.push_back(E[e]);
                        sort(edges.begin(), edges.end());
                        auto code = encode(n, edges);
                        assert((int)code.size() == n - 2 && decode(n, code) == edges);
                        for (int v = 0; v < n; v++) assert(count(code.begin(), code.end(), v) == deg[v] - 1);
                    }
                }
                set<int> rootsOf; bool okRoots = true; // vertices 0..k-1 in distinct components
                for (int v = 0; v < k; v++) okRoots &= rootsOf.insert(f(v)).second;
                if (okRoots) forests[k]++;
                return;
            }
            go(i + 1);
            pick.push_back(i); go(i + 1); pick.pop_back();
        };
        go(0);
        assert(trees == (n == 1 ? 1 : (ll)llround(pow(n, n - 2))));
        if (n >= 2) for (auto& [deg, cnt] : byDeg) {
            ll num = 1, den = 1; for (int i = 2; i <= n - 2; i++) num *= i;
            for (int d : deg) for (int i = 2; i <= d - 1; i++) den *= i;
            assert(cnt == num / den);
        }
        for (int k = 1; k < n; k++) assert(forests[k] == k * (ll)llround(pow(n, n - k - 1)));
        if (n >= 2) { // every sequence decodes to a tree whose code is that sequence
            ll total = 1; for (int i = 0; i < n - 2; i++) total *= n;
            set<vector<pair<int, int>>> seen;
            for (ll x = 0; x < total; x++) {
                vector<int> code(n - 2); ll y = x; for (auto& v : code) v = y % n, y /= n;
                auto edges = decode(n, code);
                assert((int)edges.size() == n - 1 && encode(n, edges) == code);
                seen.insert(edges);
            }
            assert((ll)seen.size() == total && total == trees);
        }
    }
    // Joining k fixed components of sizes s_i into one tree: n^(k-2) * prod s_i.
    for (int n = 2; n <= 6; n++) {
        vector<int> g(n);
        function<void(int, int)> go = [&](int i, int k) { // components as restricted growth strings
            if (i < n) { for (int v = 0; v <= k; v++) g[i] = v, go(i + 1, max(k, v + 1)); return; }
            if (k < 2) return;
            vector<pair<int, int>> cross;
            for (int a = 0; a < n; a++) for (int b = a + 1; b < n; b++) if (g[a] != g[b]) cross.push_back({g[a], g[b]});
            ll ways = 0;
            for (int mask = 0; mask < (1 << cross.size()); mask++) {
                if (__builtin_popcount(mask) != k - 1) continue;
                vector<int> par(k); iota(par.begin(), par.end(), 0);
                function<int(int)> f = [&](int x) { return par[x] == x ? x : par[x] = f(par[x]); };
                bool ok = true;
                for (int e = 0; e < (int)cross.size() && ok; e++) if (mask >> e & 1) {
                    int a = f(cross[e].first), b = f(cross[e].second);
                    if (a == b) ok = false; else par[a] = b;
                }
                ways += ok;
            }
            ll want = 1; for (int t = 0; t < k - 2; t++) want *= n;
            for (int comp = 0; comp < k; comp++) want *= count(g.begin(), g.end(), comp);
            assert(ways == want);
        };
        go(0, 0);
    }

    // Burnside: necklaces, bracelets, rotated grids against orbit enumeration.
    auto ipow = [](ll b, int e) { ll r = 1; while (e--) r *= b; return r; };
    for (int n = 1; n <= 8; n++) for (int k = 1; k <= 4; k++) {
        set<vector<int>> neck, brace;
        vector<int> s(n);
        for (ll code = 0; code < ipow(k, n); code++) {
            ll x = code; for (int i = 0; i < n; i++) s[i] = x % k, x /= k;
            vector<int> best = s, bestR = s;
            for (int r = 0; r < n; r++) {
                vector<int> t(n), u(n);
                for (int i = 0; i < n; i++) t[i] = s[(i + r) % n], u[i] = s[(n - 1 - i + r) % n];
                best = min(best, t); bestR = min({bestR, t, u});
            }
            neck.insert(best); brace.insert(bestR);
        }
        ll sumG = 0, sumPhi = 0;
        for (int i = 0; i < n; i++) sumG += ipow(k, __gcd(i, n) ? __gcd(i, n) : n);
        for (int d = 1; d <= n; d++) if (n % d == 0) sumPhi += phi(d) * ipow(k, n / d);
        assert(sumG % n == 0 && sumG / n == (ll)neck.size() && sumPhi == sumG);
        ll twice4 = 2 * sumG / n; // bracelets = (N + R) / 2, so 4 * bracelets = 2N + 2R
        twice4 += n % 2 ? 2 * ipow(k, (n + 1) / 2) : ipow(k, n / 2) + ipow(k, n / 2 + 1);
        assert(twice4 % 4 == 0 && twice4 / 4 == (ll)brace.size());
    }
    for (int n = 1; n <= 4; n++) for (int k = 1; k <= 3; k++) {
        if (ipow(k, n * n) > 300000) continue;
        set<vector<int>> orbits;
        vector<int> g(n * n);
        for (ll code = 0; code < ipow(k, n * n); code++) {
            ll x = code; for (auto& v : g) v = x % k, x /= k;
            vector<int> best = g, cur = g;
            for (int t = 0; t < 3; t++) {
                vector<int> nx(n * n);
                for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) nx[j * n + (n - 1 - i)] = cur[i * n + j];
                cur = nx; best = min(best, cur);
            }
            orbits.insert(best);
        }
        ll f = ipow(k, n * n) + ipow(k, (n * n + 1) / 2) + 2 * ipow(k, (n * n + 3) / 4);
        assert(f % 4 == 0 && f / 4 == (ll)orbits.size());
    }

    // Manhattan <-> Chebyshev, and Pick on convex lattice polygons.
    for (int it = 0; it < 20000; it++) {
        auto coord = [&] { return (ll)(rng() % 2001) - 1000; }; // signed: rng() is unsigned
        ll x1 = coord(), y1 = coord(), x2 = coord(), y2 = coord();
        ll du = (x1 + y1) - (x2 + y2), dv = (x1 - y1) - (x2 - y2);
        assert(llabs(x1 - x2) + llabs(y1 - y2) == max(llabs(du), llabs(dv)));
        assert(2 * max(llabs(x1 - x2), llabs(y1 - y2)) == llabs(du) + llabs(dv));
    }
    for (int it = 0; it < 2000; it++) { // farthest Manhattan pair from the ranges of u and v
        int n = 1 + rng() % 12;
        vector<ll> x(n), y(n);
        for (int i = 0; i < n; i++) x[i] = (ll)(rng() % 201) - 100, y[i] = (ll)(rng() % 201) - 100;
        ll brute = 0, umin = LLONG_MAX, umax = LLONG_MIN, vmin = LLONG_MAX, vmax = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) brute = max(brute, llabs(x[i] - x[j]) + llabs(y[i] - y[j]));
            umin = min(umin, x[i] + y[i]), umax = max(umax, x[i] + y[i]);
            vmin = min(vmin, x[i] - y[i]), vmax = max(vmax, x[i] - y[i]);
        }
        assert(brute == max(umax - umin, vmax - vmin));
    }
    for (int it = 0; it < 300; it++) {
        int n = 3 + rng() % 8, R = 2 + rng() % 9;
        vector<pair<ll, ll>> pts(n);
        for (auto& [x, y] : pts) x = (ll)(rng() % (2 * R + 1)) - R, y = (ll)(rng() % (2 * R + 1)) - R;
        sort(pts.begin(), pts.end()); pts.erase(unique(pts.begin(), pts.end()), pts.end());
        auto cr = [](pair<ll, ll> o, pair<ll, ll> a, pair<ll, ll> b) { return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first); };
        vector<pair<ll, ll>> h;
        for (int pass = 0; pass < 2; pass++) {
            size_t st = h.size();
            for (auto q : pts) { while (h.size() >= st + 2 && cr(h[h.size() - 2], h.back(), q) <= 0) h.pop_back(); h.push_back(q); }
            h.pop_back(); reverse(pts.begin(), pts.end());
        }
        if (h.size() < 3) continue;
        ll A2 = 0, B = 0;
        for (size_t i = 0; i < h.size(); i++) {
            auto a = h[i], b = h[(i + 1) % h.size()];
            A2 += a.first * b.second - a.second * b.first;
            B += __gcd(llabs(a.first - b.first), llabs(a.second - b.second));
        }
        ll I = 0, onB = 0;
        for (ll x = -R; x <= R; x++) for (ll y = -R; y <= R; y++) {
            bool in = true, edge = false;
            for (size_t i = 0; i < h.size(); i++) {
                auto a = h[i], b = h[(i + 1) % h.size()];
                ll v = cr(a, b, {x, y});
                if (v < 0) in = false;
                if (v == 0 && min(a.first, b.first) <= x && x <= max(a.first, b.first) && min(a.second, b.second) <= y && y <= max(a.second, b.second)) edge = true;
            }
            if (edge) onB++; else if (in) I++;
        }
        assert(onB == B && A2 == 2 * I + B - 2);
    }
    puts("counting formulas: ok");
}
