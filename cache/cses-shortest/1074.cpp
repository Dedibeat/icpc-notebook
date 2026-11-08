#import <regex>
 
long s, v['   '], *j=v,*i=v-1;
 
main()
{
    for (; ~scanf("%d", i++););
    for (std::sort(v, i); --i > j++; s += *i - *j);
    printf("%ld", s);
}