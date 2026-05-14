int getRoot(int u) {
  if (u == dsu[u]) return u;
  return dsu[u] = getRoot(dsu[u]);
}

void addEdge(int u, int v) {
  u = getRoot(u); v = getRoot(v);

  dsu[n] = n;
  dsu[u] = dsu[v] = n;

  adj[n].push_back(u);
  if (u != v) adj[n].push_back(v);

  ++n;
}

void build() {
  for (int i = 0; i < n; ++i) dsu[i] = i;
  for (int i = 0; i < m; ++i) addEdge(U[i], V[i]);
}
