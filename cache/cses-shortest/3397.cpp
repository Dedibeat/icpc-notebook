#import<iostream>

using namespace std;

#define S for(i=n-1;i>=0;i--){
#define Q cin>>k;k--;

main()
{
    long long n,k,i,j,c,F[20]={1};Q
    for(i=1;i<20;i++)
        F[i]=i*F[i-1];
    while(cin>>i>>n)
        {bool p[n]={};
        if(i-1)
            {c=1;
            S
                Q
                p[k]=1;
                for(j=k-1;j>=0;j--)
                    k-=p[j];
                c+=k*F[i];}
            cout<<c;}
        else
            {Q
            S
                c=k/F[i];
                for(j=0;c>=0;j++)
                    c-=!p[j];
                p[j-1]=1;
                k%=F[i];
                cout<<j<<" ";}}
        cout<<"\n";}
}