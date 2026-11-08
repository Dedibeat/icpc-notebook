#import <iostream>
using namespace std;
int u['   '][20],x,y,i,j;
 
#define Y cin >> x >> y
main(){
   for(cin>>j>>x;j--;)Y,*u[y]=max(*u[y],x);
   for(i=1;i<='   ';i++){
       *u[i]=max(*u[i],*u[i-1]);
       for(j=0;j<19;)u[i][++j]=u[u[i][j]][j];
   }
   for(;Y;cout << j << ' ') for(i=19, j = 0;~i;--i)u[y][i]>=x ? j|=1<<i,y=u[y][i] : 1;
   
}