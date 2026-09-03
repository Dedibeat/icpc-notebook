// Evaluate degree < n polynomial from y[i]=f(i), modulo prime LAGRANGE_MOD.
// Complexity: O(n + log MOD) time, O(n) memory per evaluation.
// Pitfalls: n<MOD; values/x are interpreted modulo MOD; MOD must be prime.
// Usage: long long value=lagrangeConsecutive(y,x);
const long long LAGRANGE_MOD=1000000007;
long long lagPow(long long a,long long e) {
    long long r=1;
    for(;e;e>>=1,a=a*a%LAGRANGE_MOD) if(e&1) r=r*a%LAGRANGE_MOD;
    return r;
}
long long lagrangeConsecutive(vector<long long> y,long long x) {
    int n=y.size(); if(!n) return 0;
    x=(x%LAGRANGE_MOD+LAGRANGE_MOD)%LAGRANGE_MOD;
    for(auto& v:y) v=(v%LAGRANGE_MOD+LAGRANGE_MOD)%LAGRANGE_MOD;
    if(x<n) return y[x];
    vector<long long> pre(n+1,1),suf(n+1,1),fact(n),ifact(n);
    for(int i=0;i<n;++i) pre[i+1]=pre[i]*(x-i+LAGRANGE_MOD)%LAGRANGE_MOD;
    for(int i=n-1;i>=0;--i) suf[i]=suf[i+1]*(x-i+LAGRANGE_MOD)%LAGRANGE_MOD;
    fact[0]=1;for(int i=1;i<n;++i)fact[i]=fact[i-1]*i%LAGRANGE_MOD;
    ifact[n-1]=lagPow(fact[n-1],LAGRANGE_MOD-2);
    for(int i=n-1;i;--i)ifact[i-1]=ifact[i]*i%LAGRANGE_MOD;
    long long ans=0;
    for(int i=0;i<n;++i) {
        long long term=y[i]*pre[i]%LAGRANGE_MOD*suf[i+1]%LAGRANGE_MOD;
        term=term*ifact[i]%LAGRANGE_MOD*ifact[n-1-i]%LAGRANGE_MOD;
        if((n-1-i)&1) ans=(ans-term+LAGRANGE_MOD)%LAGRANGE_MOD;
        else ans=(ans+term)%LAGRANGE_MOD;
    }
    return ans;
}
