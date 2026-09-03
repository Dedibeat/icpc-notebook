#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/mo_algorithm.cpp"

int main(){mt19937 rng(33);for(int n=0;n<=100;++n){vector<int>a(n);for(int&x:a)x=rng()%15;vector<pair<int,int>>q(300);for(auto&[l,r]:q){l=rng()%(n+1);r=rng()%(n+1);if(l>r)swap(l,r);}vector<int>freq(15);int distinct=0;auto add=[&](int i){distinct+=freq[a[i]]++==0;};auto rem=[&](int i){distinct-=--freq[a[i]]==0;};auto got=mo_solve(n,q,add,rem,[&]{return distinct;});for(int z=0;z<(int)q.size();++z){set<int>s(a.begin()+q[z].first,a.begin()+q[z].second);assert(got[z]==(int)s.size());}}}
