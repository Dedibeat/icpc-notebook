#import<iostream>

long dp['  ']['  '],i,j,l=1,M=1e9+7,C['  ']['  '],n;

main()
{
    std::string s;std::cin>>s;
    for(n=s.size();i<=n;i++)
        {dp[i][i]=C[i][0]=C[i][i]=1;
        for(j=1;j<i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;}
    for(;l<=n;l++)
        for(i=0;i+l<=n;i++)
            for(j=1;j<l;j++)
                if(s[i]==s[i+j])
                    dp[i][i+l]+=dp[i+1][i+j]*dp[i+j+1][i+l]%M*C[l/2][(j+1)/2]%M,
                    dp[i][i+l]%=M;
    std::cout<<dp[0][n];
}