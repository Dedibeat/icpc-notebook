// Segment tree beats: range add/chmin/chmax and range sum/min/max on [l,r).
// Reference: Ji Ruyi's strict-second-extrema formulation.
// Complexity: add/query O(log n); chmin/chmax amortized O(log^2 n).
// Pitfalls: mx2/mn2 are STRICT second extrema; comparisons in the fast-path
//           conditions must stay strict. Keep values far inside +/-INF; sums
//           and lazy additions can overflow long long.
// Input: initial values and valid 0-indexed half-open intervals [l,r).
// Effect: add adds; chmin caps from above; chmax floors from below on [l,r).
// Output: sum/min/max aggregate [l,r); empty ranges give 0/INF/NINF.
struct SegTreeBeats {
    using ll=long long;
    static constexpr ll INF=(1LL<<60),NINF=-INF;
    struct Node {
        ll sum=0,mx1=NINF,mx2=NINF,mn1=INF,mn2=INF,add=0;
        int mxc=0,mnc=0;
    };
    int n;
    vector<Node>t;
    SegTreeBeats(const vector<ll>&a={}){init(a);}
    Node mergeNode(const Node&a,const Node&b) {
        Node c;c.sum=a.sum+b.sum;
        if(a.mx1==b.mx1)c.mx1=a.mx1,c.mxc=a.mxc+b.mxc,c.mx2=std::max(a.mx2,b.mx2);
        else if(a.mx1>b.mx1)c.mx1=a.mx1,c.mxc=a.mxc,c.mx2=std::max(a.mx2,b.mx1);
        else c.mx1=b.mx1,c.mxc=b.mxc,c.mx2=std::max(a.mx1,b.mx2);
        if(a.mn1==b.mn1)c.mn1=a.mn1,c.mnc=a.mnc+b.mnc,c.mn2=std::min(a.mn2,b.mn2);
        else if(a.mn1<b.mn1)c.mn1=a.mn1,c.mnc=a.mnc,c.mn2=std::min(a.mn2,b.mn1);
        else c.mn1=b.mn1,c.mnc=b.mnc,c.mn2=std::min(a.mn1,b.mn2);
        return c;
    }
    void init(const vector<ll>&a){n=a.size();t.assign(4*std::max(1,n),{});if(n)build(1,0,n,a);}
    void build(int x,int l,int r,const vector<ll>&a){
        if(r-l==1){t[x].sum=t[x].mx1=t[x].mn1=a[l];t[x].mxc=t[x].mnc=1;return;}
        int m=(l+r)/2;build(2*x,l,m,a);build(2*x+1,m,r,a);t[x]=mergeNode(t[2*x],t[2*x+1]);
    }
    void applyAdd(int x,ll v,int len){auto&z=t[x];z.sum+=v*len;z.mx1+=v;if(z.mx2!=NINF)z.mx2+=v;z.mn1+=v;if(z.mn2!=INF)z.mn2+=v;z.add+=v;}
    void applyChmin(int x,ll v){auto&z=t[x];z.sum+=(v-z.mx1)*z.mxc;if(z.mn1==z.mx1)z.mn1=v;else if(z.mn2==z.mx1)z.mn2=v;z.mx1=v;}
    void applyChmax(int x,ll v){auto&z=t[x];z.sum+=(v-z.mn1)*z.mnc;if(z.mx1==z.mn1)z.mx1=v;else if(z.mx2==z.mn1)z.mx2=v;z.mn1=v;}
    void push(int x,int l,int r){
        int m=(l+r)/2;
        if(t[x].add){applyAdd(2*x,t[x].add,m-l);applyAdd(2*x+1,t[x].add,r-m);t[x].add=0;}
        if(t[2*x].mx1>t[x].mx1)applyChmin(2*x,t[x].mx1);
        if(t[2*x+1].mx1>t[x].mx1)applyChmin(2*x+1,t[x].mx1);
        if(t[2*x].mn1<t[x].mn1)applyChmax(2*x,t[x].mn1);
        if(t[2*x+1].mn1<t[x].mn1)applyChmax(2*x+1,t[x].mn1);
    }
    void add(int x,int l,int r,int ql,int qr,ll v){if(qr<=l||r<=ql)return;if(ql<=l&&r<=qr){applyAdd(x,v,r-l);return;}push(x,l,r);int m=(l+r)/2;add(2*x,l,m,ql,qr,v);add(2*x+1,m,r,ql,qr,v);t[x]=mergeNode(t[2*x],t[2*x+1]);}
    void chmin(int x,int l,int r,int ql,int qr,ll v){if(qr<=l||r<=ql||t[x].mx1<=v)return;if(ql<=l&&r<=qr&&t[x].mx2<v){applyChmin(x,v);return;}push(x,l,r);int m=(l+r)/2;chmin(2*x,l,m,ql,qr,v);chmin(2*x+1,m,r,ql,qr,v);t[x]=mergeNode(t[2*x],t[2*x+1]);}
    void chmax(int x,int l,int r,int ql,int qr,ll v){if(qr<=l||r<=ql||t[x].mn1>=v)return;if(ql<=l&&r<=qr&&t[x].mn2>v){applyChmax(x,v);return;}push(x,l,r);int m=(l+r)/2;chmax(2*x,l,m,ql,qr,v);chmax(2*x+1,m,r,ql,qr,v);t[x]=mergeNode(t[2*x],t[2*x+1]);}
    Node query(int x,int l,int r,int ql,int qr){if(ql<=l&&r<=qr)return t[x];push(x,l,r);int m=(l+r)/2;if(qr<=m)return query(2*x,l,m,ql,qr);if(m<=ql)return query(2*x+1,m,r,ql,qr);return mergeNode(query(2*x,l,m,ql,qr),query(2*x+1,m,r,ql,qr));}
    void add(int l,int r,ll v){if(l<r)add(1,0,n,l,r,v);}
    void chmin(int l,int r,ll v){if(l<r)chmin(1,0,n,l,r,v);}
    void chmax(int l,int r,ll v){if(l<r)chmax(1,0,n,l,r,v);}
    ll sum(int l,int r){return l<r?query(1,0,n,l,r).sum:0;}
    ll min(int l,int r){return l<r?query(1,0,n,l,r).mn1:INF;}
    ll max(int l,int r){return l<r?query(1,0,n,l,r).mx1:NINF;}
};
