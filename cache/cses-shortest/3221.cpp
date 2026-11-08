#import<bits/stdc++.h>

#define S std::

long n,k,x,a,b,c,i,e;

main()
{
    S cin>>n>>k>>x>>a>>b>>c;
    for(S priority_queue<S pair<int,int>> q;i<n;x=(a*x+b)%c)
        {q.push({-x,i++});
        if(i>=k)
            {while(q.top().second<i-k)
                q.pop();
            e^=-q.top().first;}}
    S cout<<e;
}