#import <bits/stdc++.h>
using namespace std;
const int N= '   ';
#define _ [N]
int n,q,rt,v _,sz _,tg _,lc _,rc _;
char s _;
mt19937 rnd(time(0));
void U(int N) {sz _=sz[lc _]+sz[rc _]+1;}
void rev(int N) {swap(lc _,rc _);tg _^=1;}
void P(int N){
	if(tg _) rev(lc _),rev(rc _),tg _=0;
}
void S(int N,int k,int&x,int&y){
	if(!N) {x=y=0;return;}
	P(N);
	if(sz[lc _]<k) S(rc[x=N],k-sz[lc _]-1,rc _,y);
	else S(lc[y=N],k,x,lc _);
	U(N);
}
int M(int x,int N){
	if(!x||!N) return x|N;
	if(v[x]<v _) return P(x),rc[x]=M(rc[x],N),U(x),x;
	return P(N),lc _=M(x,lc _),U(N),N;
}
void T(int N){
	if(!N) return;
	P(N);
	T(lc _);
	putchar(s _);
	T(rc _);
}
main(){
	cin >> n >>q;
	for(int N=1;N<=n;N++)cin >> s _, v _=rnd(),sz _=1,rt=M(rt,N);
	for(int l,r,x,y,z;q--;){
		cin >> l >> r;
		S(rt,r,x,y);
		S(x,l-1,x,z);
		rev(z);
		rt=M(M(x,z),y);
	}
	T(rt);
}