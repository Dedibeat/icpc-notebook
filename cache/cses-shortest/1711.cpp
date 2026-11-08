#include <bits/stdc++.h>

using namespace std;
const int N = 500;
int a, b, m, n, f, k, g[N][N], h[N][N], e[N][N];
vector<int> p, s;

int x(int i) {
  s[i] = 1;
  if (i == n - 1) {
    f++;
    return 1;
  }
  for (int j = 0; j < n; j++)
    if (!s[j] && g[i][j])
      if (x(j)) {
        g[i][j]--, g[j][i]++;
        return 1;
      }
  return 0;
}

int y(int i) {
  p.push_back(i + 1);
  if (!i) return 1;
  for (int j = 0; j < n; j++)
    if (g[i][j] && h[j][i] && !e[i][j]) {
      e[i][j] = 1;
      if (y(j)) return 1;
      e[i][j] = 0;
    }
  p.pop_back();
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    a--, b--;
    g[a][b] = h[a][b] = 1;
  }
  s.resize(n, 0);
  while (x(0)) fill(&s[0], &s[0] + n, 0);
  cout << f << '\n';
  while (f--) {
    p.clear();
    y(n - 1);
    k = p.size();
    cout << k << '\n';
    for (int i = k - 1; i >= 0; i--) cout << p[i] << " \n"[!i];
  }
}
