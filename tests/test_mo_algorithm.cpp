#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/mo_algorithm.cpp"

void check(const vector<int>& a, const vector<pair<int,int>>& queries, int sigma) {
    auto got=mo_distinct(a,queries,sigma);
    assert(got.size()==queries.size());
    for(int i=0;i<(int)queries.size();++i) {
        auto [l,r]=queries[i];
        set<int> values(a.begin()+l,a.begin()+r);
        assert(got[i]==(int)values.size());
    }
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
