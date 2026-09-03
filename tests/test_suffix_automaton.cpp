#include <bits/stdc++.h>
using namespace std;
#include "../sections/string/suffix_automaton.cpp"

int main() {
    mt19937 rng(16);
    for(int n=0;n<=18;++n) for(int it=0;it<100;++it) {
        string s;for(int i=0;i<n;++i)s+=char('a'+rng()%3);
        SuffixAutomaton sam(s);
        set<string> all;
        for(int l=0;l<n;++l)for(int r=l+1;r<=n;++r)all.insert(s.substr(l,r-l));
        assert(sam.distinctSubstrings()==(long long)all.size());
        assert(sam.occurrences("")==n+1);
        for(int len=1;len<=5;++len)for(int q=0;q<30;++q){
            string t;for(int i=0;i<len;++i)t+=char('a'+rng()%3);
            long long occ=0;for(int p=0;p+len<=n;++p)occ+=s.substr(p,len)==t;
            assert(sam.contains(t)==(occ>0));
            assert(sam.occurrences(t)==occ);
        }
    }
}
