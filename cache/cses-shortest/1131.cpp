#import<bits/stdc++.h>
#define S std::
using i=int;
S map<i,i>C['   '];
i D,a,b;
i s(i c, i d=0, i p=0) {
    for (auto [x,y] : C[d>D?D = d,b = c:c])
        x^p&&s(x, d+1, c);
}
main(){
    for(S cin>>a;S cin>>a>>b;C[a][b])C[b][a];
    s(1);
    s(b);
    S cout << D;
}
