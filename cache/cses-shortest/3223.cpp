#import<bits/stdc++.h>

long n,k,i,u,l,r,s,x['   '],t['   '];

#define S std::
#define F(x,y,k,v) for(l=k;l;l/=2)t[l]+=v; for(l=x,r=y,u=0;l<=r;l/=2,r/=2){if(l%2) u+=t[l++];if(!(r%2)) u+=t[r--];} s+=v*u;

main()
{
    S map<int,int> M;
    for(S cin>>n>>k;S cin>>x[l];)
        M[x[l++]];
    for(auto [o,w] : M)
        M[o]=u++;
    while(i<n)
        {u=n+M[x[i++]];
        F(u+1,2*n-1,u,1)
        if(i>=k)
            {S cout<<s<<" ";
            u=n+M[x[i-k]];
            F(n,u-1,u,-1)}}
}