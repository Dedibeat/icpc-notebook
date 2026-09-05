// Mo example: number of distinct values in each static query [l,r).
// Input: static compressed a[i] in [0,sigma), queries as valid [l,r) pairs.
// Output: distinct counts in query input order; an empty interval gives 0.
// O((n+q)*sqrt(n)) moves + O(q log q) sorting; O(q+sigma) extra space.
vector<int> mo_distinct(const vector<int>& a,
        const vector<pair<int,int>>& queries, int sigma) {
    int n=a.size(), q=queries.size(), block=max(1,(int)sqrt(n));
    vector<int> order(q), ans(q), freq(sigma);
    iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int i,int j) {
        int bi=queries[i].first/block, bj=queries[j].first/block;
        if(bi!=bj) return bi<bj;
        return (bi&1) ? queries[i].second>queries[j].second
                      : queries[i].second<queries[j].second;
    });
    int l=0, r=0, distinct=0;
    // Adapt these updates and ans[id] for another window statistic.
    auto add = [&](int i) { distinct += freq[a[i]]++ == 0; };
    auto remove = [&](int i) { distinct -= --freq[a[i]] == 0; };
    for(int id:order) {
        auto [ql,qr]=queries[id];
        while(l>ql) add(--l);
        while(r<qr) add(r++);
        while(l<ql) remove(l++);
        while(r>qr) remove(--r);
        ans[id]=distinct;
    }
    return ans;
}
