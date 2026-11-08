#import <iostream>

#define I int
I n,i,j,a['   '];

void s(I z=0){
    if(j<n&&a[n+j]!=z){
        I u=a[i++];
        s(u);
        j++;
        s(z);
        std::cout<<u<<" ";
    }
}

int main(){
    for(std::cin>>n;i<2*n;)std::cin>>a[i++];
    s(i=0);
}