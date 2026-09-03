#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/segment_tree_beats.cpp"

int main(){mt19937 rng(44);SegTreeBeats empty;assert(empty.sum(0,0)==0);for(int n=1;n<=80;++n){vector<long long>a(n);for(auto&x:a)x=(int)(rng()%101)-50;SegTreeBeats st(a);for(int it=0;it<3000;++it){int l=rng()%(n+1),r=rng()%(n+1);if(l>r)swap(l,r);long long x=(int)(rng()%101)-50;int type=rng()%6;if(type==0){st.add(l,r,x);for(int i=l;i<r;++i)a[i]+=x;}if(type==1){st.chmin(l,r,x);for(int i=l;i<r;++i)a[i]=min(a[i],x);}if(type==2){st.chmax(l,r,x);for(int i=l;i<r;++i)a[i]=max(a[i],x);}if(type==3)assert(st.sum(l,r)==accumulate(a.begin()+l,a.begin()+r,0LL));if(type==4)assert(st.min(l,r)==(l<r?*min_element(a.begin()+l,a.begin()+r):SegTreeBeats::INF));if(type==5)assert(st.max(l,r)==(l<r?*max_element(a.begin()+l,a.begin()+r):SegTreeBeats::NINF));}}}
