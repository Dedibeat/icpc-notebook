// Digit DP example: count x in [0,limit] with digit sum exactly target.
// Complexity: O(digits^2 * 10) time, O(digits^2) memory per call.
// Pitfalls: leading zeroes represent shorter numbers; 0 is counted when
//           target=0. This version assumes -1 <= limit <= 1e18.
// Usage: count_digit_sum(r,s)-count_digit_sum(l-1,s);
long long count_digit_sum(long long limit,int target) {
    if(limit<0 || target<0 || target>171) return 0;
    string digits=to_string(limit);
    long long memo[20][172];
    memset(memo,-1,sizeof memo);
    function<long long(int,int,bool)> dfs=[&](int pos,int sum,bool tight)->long long {
        if(sum>target) return 0;
        if(pos==(int)digits.size()) return sum==target;
        if(!tight && memo[pos][sum]!=-1) return memo[pos][sum];
        int hi=tight?digits[pos]-'0':9;
        long long ans=0;
        for(int d=0;d<=hi;++d) ans+=dfs(pos+1,sum+d,tight && d==hi);
        if(!tight) memo[pos][sum]=ans;
        return ans;
    };
    return dfs(0,0,true);
}
