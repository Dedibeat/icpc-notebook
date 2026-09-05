// Max-plus convolution of discrete concave sequences.
// c[k]=max(a[i]+b[k-i]); adjacent differences in each input are nonincreasing.
// Complexity: O(n+m) time and memory. Empty input returns {}.
// Pitfalls: output values must fit long long; invalid concavity hits assert.
// Uses __int128 for differences and sums. Usage: auto c=maxPlusConcave(a,b);
using ll = long long;
__extension__ typedef __int128 i128;

vector<ll> maxPlusConcave(const vector<ll>& a,const vector<ll>& b) {
    if(a.empty()||b.empty()) return {};
    auto concave=[](const vector<ll>& x) {
        for(int i=2;i<(int)x.size();++i)
            if((i128)x[i]-x[i-1]>(i128)x[i-1]-x[i-2]) return false;
        return true;
    };
    assert(concave(a)&&concave(b));
    vector<i128> da(a.size()-1),db(b.size()-1);
    for(int i=1;i<(int)a.size();++i) da[i-1]=(i128)a[i]-a[i-1];
    for(int i=1;i<(int)b.size();++i) db[i-1]=(i128)b[i]-b[i-1];
    vector<ll> c(a.size()+b.size()-1);
    i128 cur=(i128)a[0]+b[0];
    for(int k=0, i=0, j=0;k<(int)c.size();++k) {
        if(k) {
            if(i<(int)da.size()&&(j==(int)db.size()||da[i]>=db[j])) cur+=da[i++];
            else cur+=db[j++];
        }
        assert((i128)LLONG_MIN<=cur&&cur<=(i128)LLONG_MAX);
        c[k]=(ll)cur;
    }
    return c;
}
