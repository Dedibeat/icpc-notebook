// Input: n m q; m undirected edges u v; q independent queries u v x. 0-indexed.
// Output: YES iff u and v remain connected after deleting vertex x.
// Let N = bc.tree.size()+1. Build: O(n+m log(m+1)+N log N).
// Query: O(log N); memory: O(n+m+N log N). Depends on BlockCutTree, DSU, LCA.
void solve_vertex_removal() {
    int n,m,q; cin >> n >> m >> q;
    BlockCutTree bc(n);
    DSU d(n);
    for(int i=0,u,v;i<m;++i) {
        cin >> u >> v;
        bc.addEdge(u,v); d.unite(u,v);
    }
    bc.build();
    int root=bc.tree.size();
    LCA lca(root+1);
    lca.g=bc.tree; lca.g.resize(root+1);
    for(int v=0;v<n;++v)
        if(d.find(v)==v) lca.addEdge(root,v);
    lca.build(root);
    while(q--) {
        int u,v,x; cin >> u >> v >> x;
        bool ok=d.same(u,v);
        if(ok && d.same(u,x))
            ok=lca.dist(u,x)+lca.dist(x,v)!=lca.dist(u,v);
        cout << (ok ? "YES\n" : "NO\n");
    }
}
