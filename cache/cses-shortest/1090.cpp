#import <regex>
int a['   '], * b = a, * c = a + 3, s;
main()
{
    for (;~scanf("%d", ++b););
    for (std::sort(c, b);c < b--;c += *c + *b <= a[2])s++;
    printf("%d", s);
}