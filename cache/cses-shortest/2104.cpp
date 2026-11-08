#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")
#include<iostream>
#include<bitset>
using namespace std;
constexpr int N=100000;
bitset<N>b[26],ones;
int used[26];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(int i=0;i<26;i++)used[i]=-2;
    string s,t;
    int q,i;
    cin>>s>>q;
    for(i=0;i<s.size();i++)b[s[i]-'a'][i]=1;
    while(q--)
    {
        cin>>t;
        if(t.size()==1&&used[t[0]-'a']!=-2)
        {
            cout<<used[t[0]-'a']<<"\n";
            continue;
        }
        ones.set();
        for(i=0;i<t.size();i++)ones&=b[t[i]-'a']>>i;
        int ans=ones._Find_first();
        ans=(ans==N?-1:ans+1);
        if(t.size()==1)used[t[0]-'a']=ans;
        cout<<ans<<"\n";
    }
}
