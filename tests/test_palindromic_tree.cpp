#include <bits/stdc++.h>
using namespace std;
#include "../sections/string/palindromic_tree.cpp"

map<string,int> brute(const string&s){map<string,int>m;for(int l=0;l<(int)s.size();++l)for(int r=l;r<(int)s.size();++r){string t=s.substr(l,r-l+1),u=t;reverse(u.begin(),u.end());if(t==u)++m[t];}return m;}
int main(){mt19937 rng(40);for(int n=0;n<=30;++n)for(int it=0;it<200;++it){string s;Eertree e;for(int i=0;i<n;++i){char c='a'+rng()%3;s+=c;e.add(c);assert(e.distinct()==(int)brute(s).size());}auto want=brute(s);e.finishOccurrences();map<string,long long>got;for(int v=2;v<(int)e.tree.size();++v)got[e.palindrome(v)]=e.tree[v].occ;assert(got.size()==want.size());for(auto&[p,c]:want)assert(got[p]==c);}}
