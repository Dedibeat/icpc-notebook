#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/treap.cpp"

int main() {
    mt19937 rng(730);
    for (int n=0; n<=45; ++n) {
        pitem root=nullptr;
        vector<unique_ptr<item>> nodes;
        vector<long long> want;
        for (int i=0; i<n; ++i) {
            want.push_back(3'000'000'000LL+i);
            nodes.push_back(make_unique<item>(want.back(),rng()%11));
            merge(root,root,nodes.back().get());
        }
        for (int i=0; i<300; ++i) {
            int l=rng()%(n+1), r=rng()%(n+1);
            if (l>r) swap(l,r);
            reverse(root,l,r);
            reverse(want.begin()+l,want.begin()+r);
            pitem left,right;
            split(root,left,right,l);
            assert(cnt(left)==l && cnt(right)==n-l);
            merge(root,left,right);
            vector<long long> got;
            auto walk = [&](auto&& self,pitem t) -> void {
                if (!t) return;
                push(t);
                self(self,t->l);
                got.push_back(t->value);
                self(self,t->r);
            };
            walk(walk,root);
            assert(got==want);
        }
    }
}
