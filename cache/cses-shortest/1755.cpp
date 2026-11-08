#import<ios>
using z=std::string;
int c['  '],h,H;
z s,m;
main()
{
    for(;H=~getchar();)c[h=~H]++;
    for(;++h<'  ';s+=z(c[h]/2,h))if(c[h]&1)m+=h,++H;
    puts(data(H<2?s+m+z(rbegin(s),rend(s)):"NO SOLUTION"));
}