#import <stdio.h>
#define p putchar
 
char c, v, l[16] = "GAGCGAGTGAGCGAG";
int main(){
    while((c = getchar()) != 10){
        v |= c == 71 ? 1 : c == 84 ? 8 : c-63;
        if(v == 15) p(c), v = 0;
    }
    p(l[v]);
}