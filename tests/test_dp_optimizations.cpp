#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/knuth.cpp"
#include "../sections/dp/divide_and_conquer_dp.cpp"

int main() {
    mt19937 rng(993);
    for (int n=0; n<=30; ++n) for (int it=0; it<50; ++it) {
        vector<long long> pre(n+1);
        for (int i=0; i<n; ++i) pre[i+1]=pre[i]+(it%5 ? rng()%11 : 0);
        auto cost = [&](int l,int r) { return pre[r]-pre[l]; };
        vector<vector<long long>> dp(n+1,vector<long long>(n+1));
        for (int len=2; len<=n; ++len)
            for (int l=0,r=len; r<=n; ++l,++r) {
                dp[l][r]=LLONG_MAX;
                for (int k=l+1; k<r; ++k)
                    dp[l][r]=min(dp[l][r],dp[l][k]+dp[k][r]+cost(l,r));
            }
        assert(knuth(n,cost)==dp[0][n]);

        // A per-group penalty distinguishes exact groups from at most groups.
        auto partitionCost = [&](int l,int r) {
            long long s=cost(l,r);
            return s*s+5000;
        };
        vector<long long> prev(n+1),cur(n+1);
        int groups=n ? 1+rng()%n : 0;
        for (int g=1; g<=groups; ++g) {
            for (int j=g; j<=n; ++j) {
                cur[j]=LLONG_MAX;
                for (int k=g-1; k<j; ++k) {
                    if (g==1 && k!=0) break;
                    cur[j]=min(cur[j],prev[k]+partitionCost(k,j));
                }
            }
            prev.swap(cur);
        }
        assert(divide_and_conquer_dp(n,groups,partitionCost)==prev[n]);
    }
}
