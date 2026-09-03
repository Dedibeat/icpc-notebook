// Two concrete inclusion-exclusion helpers: union size from all intersections,
// and onto functions from n labeled items to k labeled boxes modulo mod.
// Complexity: O(2^k) / O(k^2+k log n). Memory O(k).
// Pitfalls: intersection[mask] must mean intersection of every set in mask;
//           union answer may overflow long long. mod need not be prime.
// Usage: union_size_ie(intersections); surjections_ie(n,k,mod).
__extension__ typedef __int128 IEInt;
long long union_size_ie(const vector<long long>& intersection) {
    long long ans=0;
    for(int mask=1;mask<(int)intersection.size();++mask)
        ans+=(__builtin_popcount((unsigned)mask)&1?1:-1)*intersection[mask];
    return ans;
}
long long surjections_ie(long long n,int k,long long mod) {
    assert(mod>0);
    vector<long long>C(k+1);C[0]=1;
    for(int i=1;i<=k;++i) for(int j=i;j;--j) C[j]=(C[j]+C[j-1])%mod;
    auto power=[&](long long a,long long e){long long r=1%mod;for(;e;e>>=1,a=(IEInt)a*a%mod)if(e&1)r=(IEInt)r*a%mod;return r;};
    long long ans=0;
    for(int i=0;i<=k;++i) {
        long long term=(IEInt)C[i]*power(k-i,n)%mod;
        ans=((i&1)?ans-term:ans+term)%mod;
    }
    return (ans+mod)%mod;
}
