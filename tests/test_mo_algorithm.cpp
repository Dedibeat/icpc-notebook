#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/mo_algorithm.cpp"

void check(const vector<int>& a, const vector<pair<int,int>>& queries, int sigma) {
    vector<int> freq(sigma), ans(queries.size(), -1);
    vector<char> active(a.size());
    int distinct = 0;
    long long sum = 0;
    mo(a.size(), queries, [&](int i) {
        assert(!active[i]);
        active[i] = true;
        if (++freq[a[i]] == 1) ++distinct;
        sum += a[i];
    }, [&](int i) {
        assert(active[i]);
        active[i] = false;
        if (--freq[a[i]] == 0) --distinct;
        sum -= a[i];
    }, [&](int id) {
        assert(ans[id] == -1);
        auto [l, r] = queries[id];
        for (int i = 0; i < (int)a.size(); ++i)
            assert(active[i] == (l <= i && i < r));
        set<int> values(a.begin() + l, a.begin() + r);
        assert(distinct == (int)values.size());
        assert(sum == accumulate(a.begin() + l, a.begin() + r, 0LL));
        ans[id] = distinct;
    });
    for (int count : ans) assert(count >= 0);
}
int main() {
    check({},{{0,0}},0);
    check({0},{},1);
    check({0},{{0,1},{1,1},{0,0},{0,1}},1);
    check({0,0,0,0},{{0,4},{2,4},{0,0},{1,2}},1);
    check({0,1,2,3},{{2,4},{0,4},{1,1},{0,1}},4);
    mt19937 rng(33);
    for(int n=0;n<=100;++n) {
        vector<int> a(n);
        for(int& x:a) x=rng()%15;
        vector<pair<int,int>> queries(300);
        for(auto& [l,r]:queries) {
            l=rng()%(n+1); r=rng()%(n+1);
            if(l>r) swap(l,r);
        }
        check(a,queries,15);
        reverse(queries.begin(),queries.end());
        check(a,queries,15); // repeated calls and different query order
    }
}
