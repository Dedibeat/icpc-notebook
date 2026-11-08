#import <iostream>
int n,x,a['  '],d['   '],i,j;
main(){
	for(std::cin >> n >> x;std::cin>>a[i++];);
	for(d[n=0]=1;++n<=x;)
		for(j=i;j--;)
			(d[n]+=a[j]>n?0:d[n-a[j]])%=1000000007;
	std::cout<<d[x];
}
