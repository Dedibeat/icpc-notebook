#import<ios>
char *m="DULR", g[72],z[52];
int a,i=64,t,ñ[]={8,-8,-1,1};
void y(int p){
  if((p^57 || (a+=t>46)&0) && g[p]&&(g[p+1]^g[p-1] | g[p+8]^g[p-8] | g[p+1]==g[p+8]))
	for(int s=4;!(g[p]=!s--);)
      z[t]^63 && z[t]^m[s] || (t++,y(p+ñ[s]),t--);
}
main(){
    for(gets(z);i-->9;)g[i]=i&7;
	y(9);printf("%d",a);
}
