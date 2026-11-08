#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5,S=26;
int n,lst=1,tot=1,f[N],lnk[N],len[N],ch[N][S];
char s[N];
void ins(int c){
	int p=lst,u=++tot;
	len[lst=u]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=u,p=lnk[p];
	if(!p) {lnk[u]=1;return;}
	int q=ch[p][c];
	if(len[p]+1==len[q]) {lnk[u]=q;return;}
	int nq=++tot;copy_n(ch[q],S,ch[nq]);
	lnk[nq]=lnk[q];len[nq]=len[p]+1;lnk[q]=lnk[u]=nq;
	while(p&&ch[p][c]==q) ch[p][c]=nq,p=lnk[p];
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++) ins(s[i]-'a');
	for(int i=2;i<=tot;i++) f[len[lnk[i]]+1]++,f[len[i]+1]--;
	for(int i=1,sum=0;i<=n;i++) printf("%d ",sum+=f[i]);
	return 0;
}
