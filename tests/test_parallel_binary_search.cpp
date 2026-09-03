#include <bits/stdc++.h>
using namespace std;
#include "../sections/misc/parallel_binary_search.cpp"

int main(){mt19937 rng(34);for(int it=0;it<500;++it){int n=1+rng()%20,m=rng()%30,q=1+rng()%40;vector<pair<int,int>>event(m);for(auto&[p,v]:event)p=rng()%n,v=rng()%8;struct Q{int l,r;long long need;};vector<Q>ask(q);for(auto&z:ask){z.l=rng()%n;z.r=1+rng()%n;if(z.l>=z.r)swap(z.l,z.r),++z.r;z.need=rng()%80;}vector<long long>a(n);auto reset=[&]{fill(a.begin(),a.end(),0);};auto apply=[&](int t){a[event[t].first]+=event[t].second;};auto check=[&](int id){long long s=0;for(int i=ask[id].l;i<ask[id].r;++i)s+=a[i];return s>=ask[id].need;};auto got=parallel_bs(q,m,reset,apply,check);for(int id=0;id<q;++id){reset();int want=m+1;for(int t=0;t<=m;++t){if(check(id)){want=t;break;}if(t<m)apply(t);}assert(got[id]==want);}}}
