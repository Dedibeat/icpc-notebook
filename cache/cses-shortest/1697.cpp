#import<bits/stdc++.h>

using namespace std;

#define I(u) .insert({u,j});
#define s second;
#define c cout<<
#define h x=q->first;
#define w ;while(

int n,x,i,j,a;

main()
{
    cin>>n;
    set<pair<int,int>> S,E
    w j<n)
        {cin>>x;
        j++;
        S I(x)}
    w n--)
        {auto q=S.begin(),r=S.end();
        h
        i=q->s
        S.erase(q);
        if(x>n)
            {c "IMPOSSIBLE";
            return 0;}
        q=r
        w x--)
            q--
        w q!=r)
            {h
            j=q->s
            E I(i)
            a++;
            S.erase(q++);
            S I(x-1)}}
    c a;
    for(auto u : E)
        c "\n"<<u.first<<" "<<u.s
}
