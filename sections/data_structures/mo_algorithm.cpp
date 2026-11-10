// Mo's algorithm on static queries [l,r), including empty ranges.
// Start with empty state. add/remove take an index; answer takes a query id.
// State on return represents the last processed window.
// O((n+q)*sqrt(n+1)) moves, O(q log q) sorting and O(q) extra space.
template<class Add, class Remove, class Answer>
void mo(int n, const vector<pair<int,int>>& queries, Add add, Remove remove,
        Answer answer) {
    int q=queries.size(), block=max<int>(1,sqrt(n));
    vector<int> order(q);
    iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int i,int j) {
        int bi=queries[i].first/block, bj=queries[j].first/block;
        if(bi!=bj) return bi<bj;
        return (bi&1) ? queries[i].second>queries[j].second
                      : queries[i].second<queries[j].second;
    });
    int l=0, r=0;
    for(int id:order) {
        auto [ql,qr]=queries[id];
        while(l>ql) add(--l);
        while(r<qr) add(r++);
        while(l<ql) remove(l++);
        while(r>qr) remove(--r);
        answer(id);
    }
}
