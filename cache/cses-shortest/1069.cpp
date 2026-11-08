#import <ios>
int m,r,p,c;
main()
{
	for(;c=~getchar();p=c,m>++r?:m=r)r*=p==c;
	printf("%d",m);
}

