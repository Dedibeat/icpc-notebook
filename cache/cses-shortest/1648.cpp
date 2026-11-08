#import <iostream>
#define L long
using namespace std;
L B['   '],n,I,x,y;
L u(L t){
	for(;t<=n;t+=t&-t)B[t]+=I;
}
L s(L t){
	for(I=0;t>0;t-=t&-t)I+=B[t];
	return I;
}
main(){
	for(cin >> n >> x;++y<=n;u(y))cin >> I;
	for(;cin >> I >> x >> y;I-1&&cout << s(y)-s(x-1) << ' '||(I=y-s(x)+s(x-1),u(x)));
} 
