// Lagrangian relaxation (WQS/Aliens trick) for an exact-k penalized oracle.
// solve(lambda) -> {min(base_cost + lambda*count), chosen_count}.
// Complexity: O(log(hi-lo) * oracle cost).
// Pitfalls: count must be nonincreasing in lambda and the exact-count cost must
//           have the required discrete-convex/strong-duality property.
// Usage: answer=lagrangian_exact_k(k,lo,hi,solve);
template<class Solve>
long long lagrangian_exact_k(int k,long long lo,long long hi,Solve solve) {
    long long originalLo=lo;
    assert(solve(lo).second>=k && solve(hi).second<=k);
    while(lo<hi) {
        long long mid=lo+(hi-lo)/2;
        if(solve(mid).second<=k)hi=mid;
        else lo=mid+1;
    }
    auto adjusted=[&](long long lambda) {
        auto [penalized,count]=solve(lambda);(void)count;
        return penalized-lambda*k;
    };
    long long ans=adjusted(lo);
    if(lo>originalLo)ans=max(ans,adjusted(lo-1));
    return ans;
}
template<class Solve>
long long aliens_exact_k(int k,long long lo,long long hi,Solve solve) {
    return lagrangian_exact_k(k,lo,hi,solve);
}
