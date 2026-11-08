#import<iostream>
using namespace std;
long q=-'   ',w=-'   ',r='   ',e='   ',x,y,p;
main(){
    for(cin>>x;cin>>x>>y;cout << max(q-r,w-e)<< " ")p=x-y,q=max(q,p),w=max(x+=y,w),e=min(x,e),r=min(p,r);
}
