#import<iostream>
int i,r,j,k,n;
std::string s;
main()
{
    std::cin>>s;
    for(n=size(s+=s);i<n/2;++i)
        for(r=j=k=i;++j<n&s[i]<=s[j];)i=s[i]<s[j]?k:i+1;
    std::cout<<s.substr(r,n/2);
}