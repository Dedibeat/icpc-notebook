#import<regex>
int a, b, i, c;
std::map<int, int> m;
main()
{
    for (;~scanf("%d%*[ ]%d", &a, &b);a < m[b] ? : m[b] = a);
    for (auto [e, s] : m)i > s ? : (i = e, c--);
    printf("%d", ~c);
}