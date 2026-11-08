#import<regex>
long s = 1, a['			'], * i = a - 1;
main() {
    for (;~scanf("%d", i++););
    std::sort(a, i);
    for (int j : a)s < j ? : s += j;
    printf("%ld", s);
}