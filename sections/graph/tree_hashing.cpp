// Deterministic AHU-style canonical ids for rooted/unrooted tree isomorphism.
// Complexity: O(n log n) from sorting child ids, memory O(n).
// Pitfalls: compare trees using the SAME TreeCanon object; recursive DFS depth;
//           inputs must be trees. No probabilistic collisions.
// rooted(g,r) identifies a rooted tree; centers gives its one/two centers;
// unrooted roots there so isomorphic unrooted trees get the same id.
// Example: TreeCanon c; c.unrooted(path3)==c.unrooted(star3).
struct TreeCanon {
    map<vector<int>,int> id;
    int get(vector<int> children) {
        sort(children.begin(),children.end());
        auto [it,inserted]=id.emplace(children,id.size());
        return it->second;
    }
    int rootedDfs(const vector<vector<int>>& g,int v,int p) {
        vector<int>children;
        for(int u:g[v]) if(u!=p) children.push_back(rootedDfs(g,u,v));
        return get(children);
    }
    int rooted(const vector<vector<int>>& g,int root) { return rootedDfs(g,root,-1); }
    vector<int> centers(const vector<vector<int>>& g) {
        int n=g.size();
        if(n<=2) {vector<int>c(n);iota(c.begin(),c.end(),0);return c;}
        vector<int>deg(n);queue<int>q;
        for(int v=0;v<n;++v) if((deg[v]=g[v].size())<=1)q.push(v);
        int left=n;
        while(left>2) {
            int take=q.size();left-=take;
            while(take--) {int v=q.front();q.pop();for(int u:g[v])if(--deg[u]==1)q.push(u);}
        }
        vector<int>c;while(!q.empty())c.push_back(q.front()),q.pop();return c;
    }
    int unrooted(const vector<vector<int>>& g) {
        if(g.empty()) return -1;
        auto c=centers(g);
        if(c.size()==1) return rooted(g,c[0]);
        int a=rootedDfs(g,c[0],c[1]),b=rootedDfs(g,c[1],c[0]);
        return get({min(a,b),max(a,b)}); // virtual root between the centers
    }
};
