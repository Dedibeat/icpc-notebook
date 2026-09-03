// Formal power series inverse/log/exp modulo 998244353. Depends on ntt.cpp.
// Returns first n coefficients. Complexity O(n log^2 n), memory O(n).
// Pitfalls: inverse needs a[0]!=0; log needs a[0]=1; exp needs a[0]=0;
//           n and inputs must fit the NTT modulus/2^23 limits.
// Usage: fps_inv(a,n), fps_log(a,n), fps_exp(a,n).
vector<ll> fps_inv(const vector<ll>& a,int n) {
    if(!n)return {};
    assert(!a.empty() && a[0]!=0);
    vector<ll>r={ntt_pow(a[0],NTT_MOD-2)};
    while((int)r.size()<n) {
        int next=min(n,2*(int)r.size());
        vector<ll>f(next);
        for(int i=0;i<next&&i<(int)a.size();++i)f[i]=a[i];
        auto prod=conv_ntt(f,r);prod.resize(next);
        for(ll&x:prod)x=(NTT_MOD-x)%NTT_MOD;
        prod[0]=(prod[0]+2)%NTT_MOD;
        r=conv_ntt(r,prod);r.resize(next);
    }
    return r;
}
vector<ll> fps_derivative(const vector<ll>& a) {
    vector<ll>d(max(0,(int)a.size()-1));
    for(int i=1;i<(int)a.size();++i)d[i-1]=a[i]*i%NTT_MOD;
    return d;
}
vector<ll> fps_integral(const vector<ll>& a) {
    vector<ll>inverses(a.size()+1),r(a.size()+1);if(!a.empty())inverses[1]=1;
    for(int i=2;i<=(int)a.size();++i)inverses[i]=NTT_MOD-NTT_MOD/i*inverses[NTT_MOD%i]%NTT_MOD;
    for(int i=0;i<(int)a.size();++i)r[i+1]=a[i]*inverses[i+1]%NTT_MOD;
    return r;
}
vector<ll> fps_log(const vector<ll>& a,int n) {
    if(!n)return {};
    assert(!a.empty() && a[0]==1);
    auto r=conv_ntt(fps_derivative(a),fps_inv(a,n));
    if((int)r.size()>n-1)r.resize(n-1);
    r=fps_integral(r);r.resize(n);
    return r;
}
vector<ll> fps_exp(const vector<ll>& a,int n) {
    if(!n)return {};
    assert(a.empty() || a[0]==0);
    vector<ll>r={1};
    while((int)r.size()<n) {
        int next=min(n,2*(int)r.size());
        auto logarithm=fps_log(r,next);
        vector<ll>delta(next);
        for(int i=0;i<next;++i) {
            ll value=i<(int)a.size()?a[i]:0;
            delta[i]=(value-logarithm[i]+NTT_MOD)%NTT_MOD;
        }
        delta[0]=(delta[0]+1)%NTT_MOD;
        r=conv_ntt(r,delta);r.resize(next);
    }
    return r;
}
