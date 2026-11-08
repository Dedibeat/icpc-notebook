#import <iostream>


#define S std::
#define F for(
#define C S cin >> n >> x;
#define Y ][y]
#define H h[

int n,x,y, H '   '][20],d['   '],a=1;

int r(int i){
    return d[i] ? d[i] : d[i]=r(H i Y)+1;
}

main(){

    F C a<n;) S cin >>  H ++a Y;

    F ;y<19;y++) F x=n;x;)  H x--][y+1]= H  H x Y Y;


    F  d[1]=1; C S cout << (n-x ?  H n][0] : n) << " "){
        y=0;
        a = r(n)-r(x);
        if(a<0) S swap(n,x),a=-a;

        F ;a>0;y++,a/=2) n = a&1 ?  H n Y : n;

        F y=18;y--;) if( H n Y != H x Y ) n= H n Y , x= H x Y ;
        
    }
}