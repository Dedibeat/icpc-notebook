// Intersection of left half-planes p + t*v. Depends on geometry_base.cpp.
// Returns the bounded convex polygon in CCW order; unbounded/empty -> {}.
// Complexity: O(n log n) time, O(n) memory.
// Pitfalls: add a large bounding box if the answer may be unbounded; zero
//           direction vectors are invalid; EPS controls parallel/outside tests.
// Usage: halfPlaneIntersection({{{0,0},{1,0}}, ...});
struct HalfPlane {
    P p,v;
    bool outside(P q) const { return sgn(cross(v,q-p))<0; }
};
bool hpSameDirection(const HalfPlane& a,const HalfPlane& b) {
    return sgn(cross(a.v,b.v))==0 && sgn(dot(a.v,b.v))>0;
}
P hpIntersection(const HalfPlane& a,const HalfPlane& b) {
    return a.p+a.v*(cross(b.p-a.p,b.v)/cross(a.v,b.v));
}
int hpHalf(P v) { return v.y>0 || (v.y==0 && v.x>=0) ? 0 : 1; }

vector<P> halfPlaneIntersection(vector<HalfPlane> h) {
    sort(h.begin(),h.end(),[](const HalfPlane& a,const HalfPlane& b) {
        int ha=hpHalf(a.v),hb=hpHalf(b.v);
        if(ha!=hb) return ha<hb;
        return cross(a.v,b.v)>0;
    });
    vector<HalfPlane> unique;
    for(auto line:h) {
        if(!unique.empty() && hpSameDirection(unique.back(),line)) {
            if(line.outside(unique.back().p)) unique.back()=line;
        } else unique.push_back(line);
    }
    deque<HalfPlane> q;
    for(auto line:unique) {
        while(q.size()>1 && line.outside(hpIntersection(q[q.size()-2],q.back()))) q.pop_back();
        while(q.size()>1 && line.outside(hpIntersection(q[0],q[1]))) q.pop_front();
        q.push_back(line);
    }
    while(q.size()>2 && q.front().outside(hpIntersection(q[q.size()-2],q.back()))) q.pop_back();
    while(q.size()>2 && q.back().outside(hpIntersection(q[0],q[1]))) q.pop_front();
    if(q.size()<3) return {};
    vector<P> poly;
    for(int i=0;i<(int)q.size();++i) {
        if(sgn(cross(q[i].v,q[(i+1)%q.size()].v))==0) return {};
        poly.push_back(hpIntersection(q[i],q[(i+1)%q.size()]));
    }
    return poly;
}
