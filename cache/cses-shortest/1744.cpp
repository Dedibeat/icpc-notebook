#import <iostream>
#define s std::
int d['  ']['  '],n,m,f=505,i,j,k,l;
main(){
	for(s cin >> n >> m;++i<f;j=k=0)
		for(;++j<f;d[i][j]=l){
			l = i == j ? 0 : f;
			for(;++k<j;)
				l=s min(l,d[i][j-k]+d[i][k]+1);
			for(k=i;--k;)
				l=s min(l,d[i-k][j]+d[k][j]+1);
		}
	s cout << d[n][m];
}
