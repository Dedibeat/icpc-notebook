#import <ios>
int n, a['   '], p[101], * j = p - 1;
main()
{
    for (;~scanf("%d", n ? j++ : &n););
    for (;n--;putchar(76 + *++j))
        for (int b : p)
            j[b] |= 11 - *j;
}