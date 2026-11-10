// Intersection of left half-planes p + t*v. Depends on geometry_base.cpp.
// Returns the bounded convex polygon in CCW order; unbounded/empty -> {}.
// Complexity: O(n log n) time, O(n) memory.
// Pitfalls: zero direction vectors are invalid. Scale directions so EPS
//           comparisons make sense. Add a box if you want a clipped region.
// Usage: halfPlaneIntersection({{{0,0},{1,0}}, ...});
struct HalfPlane {
    P p,v;
    bool outside(P q) const { return sgn(cross(v,q-p))<0; }
};
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
    // Merge equal-angle constraints, retaining the more restrictive one.
    vector<HalfPlane> lines;
    for(auto line:h) {
        if(!lines.empty() && sgn(cross(lines.back().v,line.v))==0 &&
           dot(lines.back().v,line.v)>0) {
            if(line.outside(lines.back().p)) lines.back()=line;
        } else lines.push_back(line);
    }
    // A cyclic direction gap of at least pi permits a recession direction.
    for(int i=0;i<(int)lines.size();++i)
        if(sgn(cross(lines[i].v,lines[(i+1)%lines.size()].v))<=0) return {};
    deque<HalfPlane> q;
    for(auto line:lines) {
        while(q.size()>1 && line.outside(hpIntersection(q[q.size()-2],q.back()))) q.pop_back();
        while(q.size()>1 && line.outside(hpIntersection(q[0],q[1]))) q.pop_front();
        if(!q.empty() && sgn(cross(q.back().v,line.v))==0) return {};
        q.push_back(line);
    }
    while(q.size()>2 && q.front().outside(hpIntersection(q[q.size()-2],q.back()))) q.pop_back();
    while(q.size()>2 && q.back().outside(hpIntersection(q[0],q[1]))) q.pop_front();
    if(q.size()<3) return {};
    vector<P> poly;
    for(int i=0;i<(int)q.size();++i) {
        if(sgn(cross(q[i].v,q[(i+1)%q.size()].v))<=0) return {};
        poly.push_back(hpIntersection(q[i],q[(i+1)%q.size()]));
    }
    return poly;
}
