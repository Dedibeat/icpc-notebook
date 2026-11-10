#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/matching.cpp"

int main() {
    bipartite b(1,2);
    b.add(0,0);
    b.add(0,1);
    assert(b.matching().size()==1 && b.matching().size()==1);

    mt19937 rng(312);
    for (int n=0; n<=6; ++n) for (int m=0; m<=6; ++m) {
        bipartite b(n,m);
        auto check = [&] {
            auto brute = [&](auto&& self, int at, int used) -> int {
                if (at==n) return 0;
                int ans=self(self,at+1,used);
                for (int to : b.g[at]) if (!(used>>to&1))
                    ans=max(ans,1+self(self,at+1,used|(1<<to)));
                return ans;
            };
            int want=brute(brute,0,0);
            auto got=b.matching();
            assert((int)got.size()==want);
            set<int> left,right;
            for (auto [at,to] : got) {
                assert(left.insert(at).second && right.insert(to).second);
                assert(find(b.g[at].begin(),b.g[at].end(),to)!=b.g[at].end());
            }
        };
        for (int i=0; i<50; ++i) {
            if (n && m) b.add(rng()%n,rng()%m);
            check();
            check();
        }
    }

    // DenseKuhn: brute force on tiny graphs, bipartite on medium ones, edge cases.
    auto checkDense = [&](DenseKuhn& d, int n, int want) {
        for (int rep=0; rep<2; ++rep) { // solve() must reset between calls
            int got=d.solve(), cnt=0;
            assert(got==want);
            vector<int> usedL(n);
            for (int r=0; r<DK_MAXR; ++r) if (d.mt[r]!=-1) {
                int l=d.mt[r];
                assert(0<=l && l<n && d.adj[l][r] && !usedL[l]++);
                ++cnt;
            }
            assert(cnt==got);
        }
    };
    for (int n=0; n<=6; ++n) for (int m=0; m<=6; ++m) for (int it=0; it<30; ++it) {
        DenseKuhn d(n);
        int p=rng()%4; // p=3: complete graph, p=0: about one edge in four
        for (int l=0; l<n; ++l) for (int r=0; r<m; ++r) if ((int)(rng()%4)<=p) d.adj[l][r]=1;
        if (it==0) for (auto& row : d.adj) row.reset(); // no edges
        auto brute = [&](auto&& self, int at, int used) -> int {
            if (at==n) return 0;
            int ans=self(self,at+1,used);
            for (int to=0; to<m; ++to) if (d.adj[at][to] && !(used>>to&1))
                ans=max(ans,1+self(self,at+1,used|(1<<to)));
            return ans;
        };
        checkDense(d,n,brute(brute,0,0));
    }
    for (int it=0; it<300; ++it) {
        int n=rng()%60, m=rng()%60, den=1+rng()%20;
        DenseKuhn d(n);
        for (int round=0; round<2; ++round) { // round 1 deletes edges and reuses d
            bipartite b(n,m);
            for (int l=0; l<n; ++l) for (int r=0; r<m; ++r) {
                if (round==0 && rng()%den==0) d.adj[l][r]=1;
                if (round==1 && rng()%2) d.adj[l][r]=0;
                if (d.adj[l][r]) b.add(l,r);
            }
            checkDense(d,n,(int)b.matching().size());
        }
    }
    DenseKuhn hi(3); // largest right id
    for (int l=0; l<3; ++l) hi.adj[l][DK_MAXR-1]=hi.adj[l][0]=1;
    checkDense(hi,3,2);
    const int N=DK_MAXR;
    DenseKuhn chain(N); // last left forces one augmenting path of length ~N
    for (int l=0; l+1<N; ++l) chain.adj[l][l]=chain.adj[l][l+1]=1;
    chain.adj[N-1][0]=1;
    checkDense(chain,N,N);
    DenseKuhn half(N); // N/2 failing searches over N/2 matched rights
    for (int l=0; l<N; ++l) for (int r=0; r<N/2; ++r) half.adj[l][r]=1;
    checkDense(half,N,N/2);
}
