// Static wavelet tree over compressed values. Index ranges are half-open [l,r).
// Complexity: build O(n log sigma); queries O(log sigma); memory O(n log sigma).
// Pitfalls: kth uses 0-based k and needs l<r; static only; values are compressed
//           internally, so negatives and duplicates work.
// kth(l,r,k) selects by 0-based order; countLess/countEqual count values in
// a[l..r). Example: wt({4,1,4,2}); kth(1,4,1)==2; countEqual(0,3,4)==2.
struct WaveletTree {
    struct Node { int lo,hi,left=-1,right=-1; vector<int>pref; };
    vector<long long>values;
    vector<Node>nodes;
    int root=-1;

    WaveletTree(const vector<long long>& a={}) { init(a); }
    int build(const vector<int>& a,int lo,int hi) {
        int x=nodes.size();nodes.push_back({lo,hi,-1,-1,{}});
        nodes[x].pref.assign(a.size()+1,0);
        if(lo==hi || a.empty()) return x;
        int mid=(lo+hi)/2;
        vector<int>L,R;L.reserve(a.size());R.reserve(a.size());
        for(int i=0;i<(int)a.size();++i) {
            bool left=a[i]<=mid;
            nodes[x].pref[i+1]=nodes[x].pref[i]+left;
            (left?L:R).push_back(a[i]);
        }
        nodes[x].left=build(L,lo,mid);
        nodes[x].right=build(R,mid+1,hi);
        return x;
    }
    void init(const vector<long long>& a) {
        values=a;sort(values.begin(),values.end());values.erase(unique(values.begin(),values.end()),values.end());
        nodes.clear();root=-1;
        if(values.empty())return;
        vector<int>rank(a.size());
        for(int i=0;i<(int)a.size();++i)rank[i]=lower_bound(values.begin(),values.end(),a[i])-values.begin();
        root=build(rank,0,values.size()-1);
    }
    int kthRank(int x,int l,int r,int k) const {
        auto& nd=nodes[x];if(nd.lo==nd.hi)return nd.lo;
        int before=nd.pref[l],inside=nd.pref[r]-before;
        if(k<inside)return kthRank(nd.left,before,nd.pref[r],k);
        return kthRank(nd.right,l-before,r-nd.pref[r],k-inside);
    }
    int countRank(int x,int l,int r,int rank) const {
        if(l>=r)return 0;
        auto& nd=nodes[x];
        if(rank<=nd.lo)return 0;
        if(nd.hi<rank)return r-l;
        int bl=nd.pref[l],br=nd.pref[r];
        return countRank(nd.left,bl,br,rank)+countRank(nd.right,l-bl,r-br,rank);
    }
    long long kth(int l,int r,int k) const {
        assert(root!=-1 && 0<=l && l<r && r<(int)nodes[root].pref.size() && 0<=k && k<r-l);
        return values[kthRank(root,l,r,k)];
    }
    int countLess(int l,int r,long long x) const {
        if(root==-1)return 0;
        int rank=lower_bound(values.begin(),values.end(),x)-values.begin();
        return countRank(root,l,r,rank);
    }
    int countEqual(int l,int r,long long x) const {
        if(root==-1)return 0;
        int rank=lower_bound(values.begin(),values.end(),x)-values.begin();
        if(rank==(int)values.size() || values[rank]!=x)return 0;
        return countRank(root,l,r,rank+1)-countRank(root,l,r,rank);
    }
};
