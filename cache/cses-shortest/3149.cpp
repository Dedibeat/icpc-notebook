#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
using VI = vector<int>;
const int NN = 2e5 + 4;
VI G[NN];
int C[NN], D[NN], jmp[NN], Fa[NN];
int dfs(int x, int fa, int d = 0) {
  D[x] = d, Fa[x] = fa, jmp[x] = x;
  int jf = jmp[fa], ans = 0;
  if (d) jmp[x] = (2 * D[jf] == D[jmp[jf]] + D[fa]) ? jmp[jf] : fa;
  for (int v : G[x])
    if (v != fa) {
      int va = dfs(v, x, d + 1);
      ans += C[v] ? (va + 2) : 0, C[x] += C[v];
    }
  return ans;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int n, q, root = 1;
  cin >> n >> q;
  REP(i, 1, n) {
    cin >> C[i];
    if (C[i]) root = i;
  }
  for (int i = 1, u, v; i < n and cin >> u >> v; i++)
    G[u].push_back(v), G[v].push_back(u);
  int cyc = dfs(root, 0);
  auto lca = [&](int u, int v) -> int {
    if (D[u] < D[v]) swap(u, v);
    while (D[u] > D[v]) u = (D[jmp[u]] >= D[v]) ? jmp[u] : Fa[u];
    while (u != v) {
      auto& p = (jmp[u] != jmp[v]) ? jmp : Fa;
      u = p[u], v = p[v];
    }
    return v;
  };
  auto nxt = [&](int v) -> int {
    while (!C[v]) v = !C[jmp[v]] ? jmp[v] : Fa[v];
    return v;
  };
  for (int u, v; q-- and cin >> u >> v;) {
    int s = nxt(u), t = nxt(v);
    printf("%d\n", cyc + (D[v] - D[t]) + (D[u] - D[s]) -
                       (D[s] + D[t] - 2 * D[lca(s, t)]));
  }
  return 0;
}