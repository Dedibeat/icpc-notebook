#import "iostream"
#define f(n) for(; i < n;i++)
#define P (1 << 21)
int a[P], b[P], n, c[P], i, j;
main()
{
	std::cin >> n;
	f(n) std::cin >> j, a[c[i]=j]++, b[j]++;
	for(j = P; j/=2; i = 0) f(P) i&j?a[i] += a[i^j]:b[i] += b[i^j];
	f(n) std::cout << a[j=c[i]] << " " << b[j] << " " << n - a[P - j -1] << ' ';
}
