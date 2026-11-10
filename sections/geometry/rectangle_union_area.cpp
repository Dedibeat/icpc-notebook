// Sweep-line area of the union of axis-aligned half-open rectangles.
// Complexity: O(n log n) time, O(n) memory.
// Pitfalls: rectangles are [x1,x2)x[y1,y2); degenerate ones are ignored;
//           spans and area use i128. The total area must fit signed i128.
// Usage: i128 area=rectangleUnionArea(rectangles);
struct Rectangle { long long x1,y1,x2,y2; };

__int128 rectangleUnionArea(const vector<Rectangle>& rectangles) {
    struct Event { long long x,y1,y2; int delta; };
    vector<Event> events;
    vector<long long> ys;
    for(auto r:rectangles) if(r.x1<r.x2 && r.y1<r.y2) {
        events.push_back({r.x1,r.y1,r.y2,1});
        events.push_back({r.x2,r.y1,r.y2,-1});
        ys.push_back(r.y1);ys.push_back(r.y2);
    }
    if(events.empty()) return 0;
    sort(events.begin(),events.end(),[](auto a,auto b){return a.x<b.x;});
    sort(ys.begin(),ys.end());ys.erase(unique(ys.begin(),ys.end()),ys.end());
    int m=ys.size()-1;
    vector<int> cover(4*m);
    vector<__int128> length(4*m);
    function<void(int,int,int)> pull=[&](int x,int l,int r){
        if(cover[x]) length[x]=(__int128)ys[r]-ys[l];
        else if(r-l==1) length[x]=0;
        else length[x]=length[2*x]+length[2*x+1];
    };
    function<void(int,int,int,int,int,int)> add=[&](int x,int l,int r,int ql,int qr,int d){
        if(qr<=l || r<=ql) return;
        if(ql<=l && r<=qr) cover[x]+=d;
        else {int mid=(l+r)/2;add(2*x,l,mid,ql,qr,d);add(2*x+1,mid,r,ql,qr,d);}
        pull(x,l,r);
    };
    __int128 area=0;
    long long prev=events[0].x;
    for(int i=0;i<(int)events.size();) {
        long long x=events[i].x;
        area+=((__int128)x-prev)*length[1];
        while(i<(int)events.size() && events[i].x==x) {
            int l=lower_bound(ys.begin(),ys.end(),events[i].y1)-ys.begin();
            int r=lower_bound(ys.begin(),ys.end(),events[i].y2)-ys.begin();
            add(1,0,m,l,r,events[i].delta);++i;
        }
        prev=x;
    }
    return area;
}
