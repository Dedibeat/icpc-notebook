#import<iostream>
long n,i,s,p=1;
main(){
    for(std::cin>>n;p;i++)
        s+=n&p?p/2*i+n%p+1:0,p<<=1;
    std::cout<<s;
}