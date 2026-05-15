struct bipartite {
    int n, m;
    vector<vector<int>> g;
    vector<int> match;

    bipartite(int n, int m): n(n), m(m), g(n), match(m, -1) {}
    
    void add(int a, int b) {
        g[a].push_back(b);
    }

    vector<bool> visited;
    bool kuhn(int v) {
        if(visited[v]) {
            return false;
        }
        visited[v] = true;
        for(auto u: g[v]) {
            if(match[u] == -1 || kuhn(match[u])) {
                match[u] = v;
                return true;
            }
        }
        return false;
    }
    
    auto matching() {
        vector<bool> paired(n);
        for(bool repeat = true; repeat;) {
            repeat = false;
            visited.assign(n, 0);
            for(int i = 0; i < n; i++) {
                if(!paired[i]) {
                    paired[i] = kuhn(i);
                    repeat |= paired[i];
                }
            }
        }
        vector<pair<int, int>> ans;
        for(int u = 0; u < m; u++) {
            if(match[u] != -1) {
                ans.emplace_back(match[u], u);
            }
        }
        return ans;
    }
};
