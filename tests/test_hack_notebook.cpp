#include "../sections/hacks/linear_recurrence.cpp"
#include "../sections/hacks/tutte_matching.cpp"
#include "../sections/hacks/vertex_cover.cpp"
#include "../sections/hacks/color_coding.cpp"
#include "../sections/hacks/bit_lcs.cpp"
#include "../sections/hacks/exact_cover.cpp"
#include "../sections/hacks/posa_path.cpp"
#include "../sections/hacks/window_subset_sum.cpp"
#include "../sections/hacks/schoning_sat.cpp"
#include "../sections/math/lagrange_interpolation.cpp"

mt19937_64 testRng(20260911);
int ri(int lo, int hi) { return pick(testRng, lo, hi); }

ll matrixTerm(vector<ll> a, vector<ll> rec, ull n) {
    int d = rec.size();
    using Mat = vector<vector<ll>>;
    auto mul = [&](Mat x, Mat y) {
        Mat z(d, vector<ll>(d));
        for (int i=0;i<d;++i) for (int j=0;j<d;++j)
            for (int k=0;k<d;++k)
                z[i][j]=(z[i][j]+x[i][k]*y[k][j])%HMOD;
        return z;
    };
    Mat t(d,vector<ll>(d)), p=t;
    for (int i=0;i<d;++i) p[i][i]=1;
    for (int i=0;i+1<d;++i) t[i][i+1]=1;
    for (int i=0;i<d;++i) t[d-1][i]=hnorm(rec[d-1-i]);
    for (;n;n>>=1,t=mul(t,t)) if(n&1)p=mul(p,t);
    ll ans=0;
    for(int i=0;i<d;++i)ans=(ans+p[0][i]*hnorm(a[i]))%HMOD;
    return ans;
}
void testRecurrence() {
    assert(berlekampMassey({}).empty());
    assert(berlekampMassey(vector<ll>(20)).empty());
    assert(nthTerm({}, {}, ULLONG_MAX)==0);
    assert(nthTerm({-1}, {1}, ULLONG_MAX)==HMOD-1);
    assert(nthTerm({0,1}, {1,1}, 10)==55);
    assert(hnorm(LLONG_MIN)==(LLONG_MIN%HMOD+HMOD)%HMOD);
    for(int it=0;it<1000;++it) {
        int d=ri(1,12); vector<ll> r(d), s(d);
        for(ll& x:r)x=ri(-10,10);
        for(ll& x:s)x=ri(-10,10);
        for(ll& x:s)x=hnorm(x);
        for(int i=d;i<2*d+45;++i) {
            ll x=0;
            for(int j=0;j<d;++j)x=hnorm(x+hnorm(r[j])*s[i-1-j]%HMOD);
            s.push_back(x);
        }
        vector<ll> samples(s.begin(),s.begin()+2*d);
        auto rec=berlekampMassey(samples);
        assert(rec.size()<=(size_t)d);
        for(int n=0;n<(int)s.size();++n)
            assert(nthTerm(samples,rec,n)==s[n]);
        if(d<=5) {
            ull n=testRng(); vector<ll> first(s.begin(),s.begin()+d);
            assert(nthTerm(first,r,n)==matrixTerm(first,r,n));
        }
    }
}
vector<pair<int,int>> graphEdges(int n, ull mask) {
    vector<pair<int,int>> e; int bit=0;
    for(int i=0;i<n;++i)for(int j=i+1;j<n;++j,++bit)
        if(mask>>bit&1)e.push_back({i,j});
    return e;
}
vector<vector<int>> adjacency(int n, const vector<pair<int,int>>& e) {
    vector<vector<int>> g(n);
    for(auto [u,v]:e)g[u].push_back(v),g[v].push_back(u);
    return g;
}
int bruteMatching(int n, const vector<pair<int,int>>& edges) {
    vector<int> adj(n),memo(1<<n,-1);
    for(auto [u,v]:edges)adj[u]|=1<<v,adj[v]|=1<<u;
    function<int(int)> solve=[&](int mask) {
        if(!mask)return 0;
        int& ans=memo[mask];if(ans!=-1)return ans;
        int u=__builtin_ctz((unsigned)mask), rest=mask^(1<<u);
        ans=solve(rest);
        for(int v=0;v<n;++v)if((rest>>v&1)&&(adj[u]>>v&1))
            ans=max(ans,1+solve(rest^(1<<v)));
        return ans;
    };
    return solve((1<<n)-1);
}
int bruteCover(int n, const vector<pair<int,int>>& e) {
    int best=n;
    for(int mask=0;mask<(1<<n);++mask) {
        bool ok=true;
        for(auto [u,v]:e)ok&=(mask>>u&1)||(mask>>v&1);
        if(ok)best=min(best,__builtin_popcount((unsigned)mask));
    }
    return best;
}
void verifyCover(int n,const vector<pair<int,int>>& e,int k,
                 const optional<vector<int>>& got) {
    if(!got)return;
    assert((int)got->size()<=k);
    set<int> s(got->begin(),got->end());assert(s.size()==got->size());
    for(int v:*got)assert(0<=v&&v<n);
    for(auto [u,v]:e)assert(s.count(u)||s.count(v));
}
void testMatchingCover() {
    for(int n=0;n<=5;++n)for(ull mask=0;mask<(1ULL<<(n*(n-1)/2));++mask) {
        auto e=graphEdges(n,mask);
        assert(tutteSize(n,e,2,testRng)==bruteMatching(n,e));
        int best=bruteCover(n,e);
        for(int k=-1;k<=n;++k) {
            auto got=vertexCover(n,e,k);
            assert(bool(got)==(best<=k));verifyCover(n,e,k,got);
        }
    }
    for(int it=0;it<300;++it) {
        int n=ri(1,12);vector<pair<int,int>>e;
        for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)
            if(ri(0,3)==0)e.push_back({i,j});
        assert(tutteSize(n,e,3,testRng)==bruteMatching(n,e));
        int k=ri(0,n);auto got=vertexCover(n,e,k);
        assert(bool(got)==(bruteCover(n,e)<=k));verifyCover(n,e,k,got);
    }
    assert(tutteSize(2,{{0,1},{1,0},{0,1}},3,testRng)==1);
    vector<pair<int,int>>star;
    for(int v=1;v<100;++v)star.push_back({0,v});
    assert(vertexCover(100,star,1)==optional<vector<int>>({{0}}));
}
bool brutePath(const vector<vector<int>>& g,int k) {
    if(!k)return true;
    function<bool(int,int,int)> dfs=[&](int v,int mask,int length) {
        if(length==k)return true;
        for(int u:g[v])if(!(mask>>u&1)&&dfs(u,mask|(1<<u),length+1))return true;
        return false;
    };
    for(int v=0;v<(int)g.size();++v)if(dfs(v,1<<v,1))return true;
    return false;
}
void verifyPath(const vector<vector<int>>& g,int k,const vector<int>& path) {
    assert((int)path.size()==k);
    set<int>s(path.begin(),path.end());assert((int)s.size()==k);
    for(int v:path)assert(0<=v&&v<(int)g.size());
    for(int i=1;i<k;++i)
        assert(find(g[path[i-1]].begin(),g[path[i-1]].end(),path[i])!=g[path[i-1]].end());
}
void testPaths() {
    assert(colorfulPath({},0,0,testRng)==optional<vector<int>>(vector<int>{}));
    assert(!colorfulPath({},1,10,testRng));
    assert(!colorfulPath({{}},1,0,testRng));
    assert(posaPath({},0,0,testRng)==optional<vector<int>>(vector<int>{}));
    assert(posaPath({{}},1,0,testRng)==optional<vector<int>>({{0}}));
    assert(!posaPath({{},{}},10,10,testRng));
    int found=0, possible=0;
    for(int it=0;it<200;++it) {
        int n=ri(1,8);vector<vector<int>>g(n);
        for(int u=0;u<n;++u)for(int v=0;v<n;++v)
            if(u!=v&&ri(0,3)==0)g[u].push_back(v);
        int k=ri(1,min(n,5));bool exists=brutePath(g,k);
        auto p=colorfulPath(g,k,180,testRng);
        if(p) {verifyPath(g,k,*p);assert(exists);++found;}
        possible+=exists;
    }
    assert(found==possible); // fixed-seed regression, not a probability proof
    int posaFound=0, posaPossible=0;
    for(int n=1;n<=5;++n)for(ull mask=0;mask<(1ULL<<(n*(n-1)/2));++mask) {
        auto g=adjacency(n,graphEdges(n,mask));bool exists=brutePath(g,n);
        auto p=posaPath(g,8,30,testRng);
        if(p) {verifyPath(g,n,*p);assert(exists);++posaFound;}
        posaPossible+=exists;
    }
    assert(posaFound>9*posaPossible/10);
    // Larger graphs with a planted Hamiltonian path; exercise many rotations.
    for(int it=0;it<100;++it) {
        int n=ri(10,35);vector<pair<int,int>>e;
        for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)
            if(j==i+1||ri(0,5)==0)e.push_back({i,j});
        auto g=adjacency(n,e);auto p=posaPath(g,20,500,testRng);
        if(p)verifyPath(g,n,*p);
    }
}
int slowLCS(const string& a,const string& b) {
    vector<int> dp(b.size()+1);
    for(char x:a) {
        int diagonal=0;
        for(int j=0;j<(int)b.size();++j) {
            int old=dp[j+1];
            dp[j+1]=x==b[j]?diagonal+1:max(dp[j],dp[j+1]);diagonal=old;
        }
    }
    return dp.back();
}
void testLCS() {
    assert(bitLCS("banana","ananas")==5);
    for(int n:{0,1,2,63,64,65,127,128,129,255})
        for(int m:{0,1,63,64,65,127,128,129,255}) {
            assert(bitLCS(string(n,'x'),string(m,'x'))==min(n,m));
            assert(bitLCS(string(n,'x'),string(m,'y'))==0);
        }
    for(int it=0;it<1500;++it) {
        string a(ri(0,260),0),b(ri(0,260),0);int alphabet=it%2?4:256;
        for(char&c:a)c=ri(0,alphabet-1);
        for(char&c:b)c=ri(0,alphabet-1);
        assert(bitLCS(a,b)==slowLCS(a,b));
    }
}
void testExactCover() {
    assert(exactCover(0,{0})==optional<vector<int>>(vector<int>{}));
    assert(!exactCover(1,{}));
    assert(exactCover(64,{~0ULL})==optional<vector<int>>({{0}}));
    vector<ull> singles;for(int i=0;i<64;++i)singles.push_back(1ULL<<i);
    assert(exactCover(64,singles)->size()==64);
    assert(!exactCover(64,{(1ULL<<63)-1}));
    for(int it=0;it<1000;++it) {
        int c=ri(0,8),r=ri(0,12);ull full=(1ULL<<c)-1;vector<ull>rows(r);
        for(ull& x:rows)x=testRng()&full;
        bool exists=false;
        for(int s=0;s<(1<<r);++s) {
            ull covered=0;bool ok=true;
            for(int i=0;i<r;++i)if(s>>i&1){ok&=!(covered&rows[i]);covered|=rows[i];}
            exists|=ok&&covered==full;
        }
        auto got=exactCover(c,rows);assert(bool(got)==exists);
        if(got){ull covered=0;for(int i:*got){assert(!(covered&rows[i]));covered|=rows[i];}assert(covered==full);}
    }
}
bool fullSubset(const vector<ll>& a,int target) {
    vector<bool> dp(target+1);dp[0]=true;
    for(ll x:a)if(x<=target)for(int j=target;j>=x;--j)dp[j]=dp[j]||dp[j-x];
    return dp[target];
}
// Independent byte DP oracle, same sampled order: tests bit shifts + clipping.
bool byteWindow(const vector<ll>& a,ll target,int W,int trials,mt19937_64& rng) {
    if(!target)return true;
    ll base=0;vector<ll>steps;
    for(ll x:a)if(x<=target-base){base+=x;steps.push_back(-x);}else steps.push_back(x);
    ll goal=target-base;if(!goal)return true;if(goal>W)return false;
    while(trials--) {
        shuffle(steps.begin(),steps.end(),rng);vector<char>dp(2*W+1);dp[W]=1;
        for(ll x:steps) {
            auto next=dp;
            for(int i=0;i<=2*W;++i)if(dp[i]) {
                __int128 j=(__int128)i+x;
                if(0<=j&&j<=2*W)next[(int)j]=1;
            }
            dp=next;
        }
        if(dp[W+goal])return true;
    }
    return false;
}
void testSubset() {
    assert(windowSubset({},0,0,0,testRng));
    assert(!windowSubset({},1,10,4,testRng));
    assert(windowSubset({LLONG_MAX},LLONG_MAX,0,0,testRng));
    assert(!windowSubset({LLONG_MAX},LLONG_MAX-1,64,3,testRng));
    for(int it=0;it<1500;++it) {
        vector<ll>a(ri(0,20));int sum=0;
        for(ll&x:a){x=ri(0,130);sum+=x;}
        int target=ri(0,sum+5),W=ri(0,180),trials=ri(0,5);
        mt19937_64 r1(it),r2(it);
        bool got=windowSubset(a,target,W,trials,r1);
        assert(got==byteWindow(a,target,W,trials,r2));
        bool exact=fullSubset(a,target);assert(!got||exact);
        assert(windowSubset(a,target,sum,1,testRng)==exact);
    }
    for(int W:{0,1,31,32,63,64,65,127,128,129}) {
        vector<ll>a{63,64,65,127,128,129,0};
        for(int t=1;t<350;++t) {
            mt19937_64 r1(t),r2(t);
            assert(windowSubset(a,t,W,2,r1)==byteWindow(a,t,W,2,r2));
        }
    }
}
bool satisfies(const vector<int>& a,const vector<vector<int>>& f) {
    for(auto& c:f) {
        bool ok=false;for(int x:c)ok|=a[abs(x)-1]==(x>0);
        if(!ok)return false;
    }
    return true;
}
void testSAT() {
    assert(schoning(0,{},0,testRng)==optional<vector<int>>(vector<int>{}));
    assert(!schoning(0,{{}},100,testRng));
    assert(!schoning(1,{{1},{-1}},100,testRng));
    assert(!schoning(1,{{1}},0,testRng));
    for(int it=0;it<500;++it) {
        int n=ri(1,8),m=ri(0,25);vector<vector<int>>f(m);
        for(auto& c:f) {
            vector<int> vars(n);iota(vars.begin(),vars.end(),1);shuffle(vars.begin(),vars.end(),testRng);
            for(int j=0,len=ri(1,min(3,n));j<len;++j)c.push_back(vars[j]*(ri(0,1)?1:-1));
        }
        bool exists=false;
        for(int mask=0;mask<(1<<n);++mask) {
            vector<int>a(n);for(int v=0;v<n;++v)a[v]=mask>>v&1;
            exists|=satisfies(a,f);
        }
        auto got=schoning(n,f,100,testRng);
        assert(bool(got)==exists);if(got)assert(satisfies(*got,f));
    }
    assert(schoning(2,{{1,1,1},{-1,2},{2,-2}},100,testRng));
}
void testLagrangeExtra() {
    assert(lagrangeConsecutive({},7)==0);
    for(ll x:{LLONG_MIN,LLONG_MAX,-1LL,0LL,HMOD,2*HMOD+2})
        assert(lagrangeConsecutive({-7},x)==HMOD-7);
    for(ll x:{LLONG_MIN,LLONG_MAX,-2LL,0LL,1LL,2LL,HMOD,HMOD+2}) {
        ll z=hnorm(x);
        assert(lagrangeConsecutive({0,1,4},x)==z*z%HMOD);
    }
}
int main() {
    testRecurrence(); cout<<"recurrence OK\n";
    testMatchingCover();cout<<"matching + vertex cover OK\n";
    testPaths();cout<<"color coding + Posa paths OK\n";
    testLCS();cout<<"bit LCS OK\n";
    testExactCover();cout<<"exact cover OK\n";
    testSubset();cout<<"window subset sum OK\n";
    testSAT();cout<<"Schoning SAT OK\n";
    testLagrangeExtra();cout<<"Lagrange boundary cases OK\n";
}
