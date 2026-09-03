#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/centroid_decomposition.cpp"

int main() {
    mt19937 rng(11);
    for (int n=1;n<=80;++n) for (int it=0;it<30;++it) {
        CentroidDecomposition cd(n);
        for (int v=1;v<n;++v) cd.addEdge(v,rng()%v);
        cd.build();
        vector<vector<int>> ct(n);
        int roots=0;
        for (int v=0;v<n;++v) {
            if (cd.parent[v]==-1) ++roots;
            else ct[cd.parent[v]].push_back(v);
        }
        assert(roots==1);
        function<vector<int>(int)> check=[&](int c) {
            vector<int> nodes={c};
            for (int u:ct[c]) {
                auto part=check(u); nodes.insert(nodes.end(),part.begin(),part.end());
            }
            vector<char> in(n); for (int v:nodes) in[v]=1;
            int largest=0;
            for (int start:nodes) if (start!=c && in[start]) {
                int cnt=0; queue<int> q; q.push(start); in[start]=0;
                while (!q.empty()) { int v=q.front();q.pop();++cnt;
                    for (int u:cd.g[v]) if (u!=c && in[u]) in[u]=0,q.push(u);
                }
                largest=max(largest,cnt);
            }
            assert(2*largest<=(int)nodes.size());
            return nodes;
        };
        int root=find(cd.parent.begin(),cd.parent.end(),-1)-cd.parent.begin();
        assert((int)check(root).size()==n);
    }
}
