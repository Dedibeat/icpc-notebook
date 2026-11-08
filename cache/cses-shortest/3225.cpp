#import<bits/stdc++.h>

using namespace std;
 
main()
{
    int n,l=-1,t='a';
    cin>>n;
    string s(n,0);
    vector<int> a(n),r(n+1,-1);
    for(int i=0;i<n;r[--a[i++]]=i)cin>>a[i];
    for(int i:a){
        if(r[i+1]<l){if(++t>'z'){cout<<-1;return 0;}
        }
        l=r[i+1];
        s[i]=t;
    }
    cout<<s;
    
    
}
