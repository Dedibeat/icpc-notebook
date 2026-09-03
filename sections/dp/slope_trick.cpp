// Slope trick for convex piecewise-linear functions with integer breakpoints.
// Supports adding constants, max(a-x,0), max(x-a,0), |x-a|, and sliding min.
// Complexity: O(log n) per hinge, O(1) shift/minimum; memory O(operations).
// Pitfalls: values/offsets can overflow long long; shift(a,b) requires a<=b.
// Usage: SlopeTrick f; f.addAbs(a); f.shift(left,right); f.minimum().
struct SlopeTrick {
    using ll=long long;
    const ll INF=(1LL<<62);
    priority_queue<ll>L;
    priority_queue<ll,vector<ll>,greater<ll>>R;
    ll addL=0,addR=0,minF=0;

    ll topL() const{return L.top()+addL;}
    ll topR() const{return R.top()+addR;}
    void pushL(ll x){L.push(x-addL);}
    void pushR(ll x){R.push(x-addR);}
    void addConstant(ll c){minF+=c;}
    void addAMinusX(ll a) { // max(a-x,0)
        if(R.empty()){pushL(a);return;}
        ll r=topR();if(a>r)minF+=a-r;
        pushR(a);r=topR();R.pop();pushL(r);
    }
    void addXMinusA(ll a) { // max(x-a,0)
        if(L.empty()){pushR(a);return;}
        ll l=topL();if(l>a)minF+=l-a;
        pushL(a);l=topL();L.pop();pushR(l);
    }
    void addAbs(ll a){addAMinusX(a);addXMinusA(a);}
    // f_new(x)=min_{x-b <= y <= x-a} f(y)
    void shift(ll a,ll b){assert(a<=b);addL+=a;addR+=b;}
    ll minimum() const{return minF;}
    pair<ll,ll> argmin() const{return {L.empty()?-INF:topL(),R.empty()?INF:topR()};}
    ll value(ll x) const { // O(number of breakpoints), mainly for debugging
        ll ans=minF;auto l=L;auto r=R;
        while(!l.empty()){ans+=max(0LL,l.top()+addL-x);l.pop();}
        while(!r.empty()){ans+=max(0LL,x-(r.top()+addR));r.pop();}
        return ans;
    }
};
