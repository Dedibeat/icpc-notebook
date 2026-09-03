// Sum floor((a*i+b)/m) for i=0..n-1, all arguments nonnegative, m>0.
// Complexity: O(log(max(a,m))) time, O(1) memory (Euclidean recurrence).
// Pitfalls: this is the nonnegative version; answer/products need i128.
// Usage: i128 ans=floor_sum(n,m,a,b);
__int128 floor_sum(long long n,long long m,long long a,long long b) {
    __int128 ans=0;
    while(true) {
        if(a>=m) {
            ans+=(__int128)(n-1)*n*(a/m)/2;
            a%=m;
        }
        if(b>=m) {
            ans+=(__int128)n*(b/m);
            b%=m;
        }
        __int128 y=(__int128)a*n+b;
        if(y<m) return ans;
        n=y/m;
        b=y%m;
        swap(a,m);
    }
}
