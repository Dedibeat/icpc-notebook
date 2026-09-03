// Mo's algorithm for offline half-open array queries [l,r).
// Complexity: O((n+q)sqrt(n) * add/remove cost), memory O(q).
// Pitfalls: add/remove must be exact inverses; reset state before the call;
//           empty ranges are allowed. This is the basic array version only.
// Usage: ans=mo_solve(n,queries,add,remove,get_answer);
template<class Add,class Remove,class Get>
auto mo_solve(int n,const vector<pair<int,int>>& queries,Add add,Remove remove,Get get) {
    using Answer=decltype(get());
    int q=queries.size(),block=max(1,(int)sqrt(max(1,n)));
    vector<int>order(q);iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int i,int j) {
        int bi=queries[i].first/block,bj=queries[j].first/block;
        if(bi!=bj) return bi<bj;
        return (bi&1)?queries[i].second>queries[j].second:
                      queries[i].second<queries[j].second;
    });
    vector<Answer>ans(q);
    int l=0,r=0;
    for(int id:order) {
        auto [ql,qr]=queries[id];
        while(l>ql) add(--l);
        while(r<qr) add(r++);
        while(l<ql) remove(l++);
        while(r>qr) remove(--r);
        ans[id]=get();
    }
    return ans;
}
