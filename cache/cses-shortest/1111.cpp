#include "bits/stdc++.h"
const int N=2e6;
char s[N];
int p[N];
main() {
    s[0]=1;
    scanf("%s",s+1);
    int n=strlen(s), mx=-1,l;
    for(int r:{0,1})
        for(int i=1,j=0;i<n;++i) {
            p[i]=p[j]+j+r>=i?std::min(p[j]+j-i,p[2*j-i]):0;
            while(s[i-p[i]]==s[i+p[i]+r]) ++p[i],j=i;
            if(p[i]*2+r>mx) mx=p[i]*2+r, l=i-p[i]+1;
        }
    s[l+mx-1]=0;
    printf("%s",s+l);
}