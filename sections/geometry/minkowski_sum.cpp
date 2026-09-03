// Minkowski sum of two nonempty strictly-convex integer polygons.
// Input polygons may be CW/rotated; output is CCW, without repeated endpoint.
// Complexity: O(n+m) after normalization, O(n+m) memory.
// Pitfalls: remove collinear hull points first; products use i128, coordinates
//           of the resulting sums must still fit long long. Depends on IP/i128.
// Usage: vector<IP> c=minkowskiSum(a,b);
i128 mpCross(IP a,IP b) { return (i128)a.x*b.y-(i128)a.y*b.x; }
i128 mpDot(IP a,IP b) { return (i128)a.x*b.x+(i128)a.y*b.y; }
IP mpAdd(IP a,IP b) { return {a.x+b.x,a.y+b.y}; }
IP mpSub(IP a,IP b) { return {a.x-b.x,a.y-b.y}; }
int mpHalf(IP a) { return a.y>0 || (a.y==0 && a.x>=0) ? 0 : 1; }
bool mpAngleLess(IP a,IP b) {
    if(mpHalf(a)!=mpHalf(b)) return mpHalf(a)<mpHalf(b);
    return mpCross(a,b)>0;
}

vector<IP> mpNormalize(vector<IP> p) {
    if(p.size()>1 && p.front().x==p.back().x && p.front().y==p.back().y) p.pop_back();
    i128 area=0;
    for(int i=0;i<(int)p.size();++i) area+=mpCross(p[i],p[(i+1)%p.size()]);
    if(area<0) reverse(p.begin(),p.end());
    int at=min_element(p.begin(),p.end(),[](IP a,IP b){return tie(a.y,a.x)<tie(b.y,b.x);})-p.begin();
    rotate(p.begin(),p.begin()+at,p.end());
    return p;
}
vector<IP> minkowskiSum(vector<IP> a,vector<IP> b) {
    a=mpNormalize(a); b=mpNormalize(b);
    if(a.size()==1) { for(auto& p:b)p=mpAdd(p,a[0]); return b; }
    if(b.size()==1) { for(auto& p:a)p=mpAdd(p,b[0]); return a; }
    vector<IP> ea(a.size()),eb(b.size());
    for(int i=0;i<(int)a.size();++i) ea[i]=mpSub(a[(i+1)%a.size()],a[i]);
    for(int i=0;i<(int)b.size();++i) eb[i]=mpSub(b[(i+1)%b.size()],b[i]);
    vector<IP> ans={mpAdd(a[0],b[0])};
    int i=0,j=0;
    while(i<(int)ea.size() || j<(int)eb.size()) {
        i128 cr=(i<(int)ea.size() && j<(int)eb.size())?mpCross(ea[i],eb[j]):0;
        IP step;
        if(i<(int)ea.size() && j<(int)eb.size() && cr==0 && mpDot(ea[i],eb[j])>0)
            step=mpAdd(ea[i++],eb[j++]);
        else if(j==(int)eb.size() || (i<(int)ea.size() && mpAngleLess(ea[i],eb[j]))) step=ea[i++];
        else step=eb[j++];
        ans.push_back(mpAdd(ans.back(),step));
    }
    ans.pop_back();
    return ans;
}
