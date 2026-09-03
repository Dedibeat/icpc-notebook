#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/digit_dp.cpp"

int digitSum(int x){int s=0;do{s+=x%10;x/=10;}while(x);return s;}
int main(){
    assert(count_digit_sum(-1,0)==0);assert(count_digit_sum(0,0)==1);
    for(int limit=0;limit<=5000;limit+=37)for(int target=0;target<=30;++target){
        long long want=0;for(int x=0;x<=limit;++x)want+=digitSum(x)==target;
        assert(count_digit_sum(limit,target)==want);
    }
}
