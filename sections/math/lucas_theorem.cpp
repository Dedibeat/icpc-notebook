// Lucas theorem: C(n,k) modulo a small prime p, even when n>=p.
// Complexity: build O(p), query O(log_p n); memory O(p).
// Pitfalls: p must be prime and small enough to allocate; n,k nonnegative.
// Usage: Lucas lucas(p); long long value=lucas.C(n,k);
struct Lucas {
    long long p;
    vector<long long>fact,ifact;
    long long power(long long a,long long e) const {
        long long r=1;
        for(;e;e>>=1,a=a*a%p) if(e&1) r=r*a%p;
        return r;
    }
    Lucas(int prime):p(prime),fact(prime),ifact(prime) {
        fact[0]=1;for(int i=1;i<p;++i)fact[i]=fact[i-1]*i%p;
        ifact[p-1]=power(fact[p-1],p-2);
        for(int i=p-1;i;--i)ifact[i-1]=ifact[i]*i%p;
    }
    long long small(int n,int k) const {
        if(k<0||k>n)return 0;
        return fact[n]*ifact[k]%p*ifact[n-k]%p;
    }
    long long C(long long n,long long k) const {
        if(k<0||k>n)return 0;
        long long ans=1;
        while(n||k) {
            int ni=n%p,ki=k%p;
            if(ki>ni)return 0;
            ans=ans*small(ni,ki)%p;n/=p;k/=p;
        }
        return ans;
    }
};
