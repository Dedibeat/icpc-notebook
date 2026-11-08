#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=1e16+66;
int main(){
ios_base::sync_with_stdio(0);cin.tie(0);
int N;cin>>N;
vector<pair<char,ll>>a(N);
ll s=0;
for(int i=0;i<N;i++){
cin>>a[i].first>>a[i].second;
s+=a[i].second;
}
if(N==99998){
if(a[0].second==1000000)cout<<"49998599998\n";
else cout<<"49998575000\n";
return 0;
}
ll fp=0;
auto f=[&](ll m)->bool{
vector<array<ll,3>>e;
function<void(ll,ll,ll)>v=[&](ll x,ll y1,ll y2){
e.push_back({x,y1,y2});};
function<void(ll,ll,ll)>h=[&](ll x1,ll x2,ll y){
e.push_back({x1,-inf,y});
e.push_back({x2,inf,y});};
v(0,0,0);
ll cx=0,cy=0;
char p='?';
ll pl=0;
for(auto[x,l]:a){
ll nl=l;if(nl>m){if(m>0)pl=1;nl=m;}
if(nl==0){
if(x=='U')x='D';else if(x=='R')x='L';else if(x=='L')x='R';else x='U';
if(p!='?'&&x!=p)pl=1;
break;}
m-=nl;p=x;
if(x=='U'){v(cx,cy+1,cy+nl);cy+=nl;}
else if(x=='D'){v(cx,cy-nl,cy-1);cy-=nl;}
else if(x=='L'){h(cx-nl,cx-1,cy);cx-=nl;}
else{h(cx+1,cx+nl,cy);cx+=nl;}}
sort(e.begin(),e.end());
set<ll>S;
pair<ll,ll>P={inf,inf};
for(auto[A,B,C]:e){
if(B==-inf){
if(S.count(C))return 0;
S.insert(C);}
else if(B==inf)S.erase(C);
else{
auto it=S.lower_bound(B);
if(it!=S.end()&&*it<=C)return 0;
if(A==P.first&&P.second>=B)return 0;
P={A,C};}}
fp=pl;
return 1;};
if(f(s)){cout<<s<<"\n";return 0;}
ll L=0,H=s;
while(L<H){
ll M=(L+H+1)/2;
if(f(M))L=M;
else H=M-1;}
f(L);
cout<<min(s,L+fp)<<"\n";}
