#include <iostream>
using namespace std;
int main()
{
    unsigned int x,y,t;
    for(cin>>x;cin>>x>>y;printf("%d\n",x+y==3?3:x==y && y<4 && y>1 ?4:t+(t-x-y)%2))
        t=max(max((x+y)/3,x/2),y/2);

}