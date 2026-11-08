#import"iostream"
using l=long;
l u=10,a,b;
l g(l a){
    return a/u&&g(a/u)|a%u==a/u%u;
}
l f(l a){
    return (a<u?a:9*f(a/u)+!g(a/u)*(a%u-9+(a/u%u>a%u)))+1;
}
main(){
    std::cin>>a>>b,std::cout<<f(b)-f(a-1);
}