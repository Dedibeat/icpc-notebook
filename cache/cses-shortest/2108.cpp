#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mxn=1e5+5;
int sa[mxn], cl[mxn], cl2[mxn], lcp[mxn];

void SA(string const& s){
    int n=s.size(), g;
    auto cmp = [&](int i, int j){
        if(cl[i]!=cl[j]) return cl[i]<cl[j];
        i+=g, j+=g;
        return i<n&&j<n?cl[i]<cl[j]:i>j;
    };
    for(int i=0;i<n;i++)
        cl[i]=s[i], sa[i]=i;
    for(g=1;;g*=2){
        sort(sa,sa+n,cmp);
        for(int i=0;i<n-1;i++)
            cl2[i+1] = cl2[i] + cmp(sa[i], sa[i+1]);
        for(int i=0;i<n;i++)
            cl[sa[i]] = cl2[i];
        if(cl2[n-1]==n-1) break;
    }
    for(int i=0,k=0;i<n;i++) if(cl[i]!=n-1){
        int j=sa[cl[i]+1];
        while(s[i+k]==s[j+k]) k++;
        lcp[cl[i]]=k;
        if(k) k--;
    }
}

int32_t main(){
    string s; cin >> s;
    int n=s.size(), k;
    cin >> k;
    SA(s);
    for(int i=0;i<n;i++){
        int x = n-sa[i]-(i?lcp[i-1]:0);
        if(x>=k){
            cout << s.substr(sa[i],lcp[i-1]+k) << "\n";
            return 0;
        }else {
            k-=x;
        }
    }
}
