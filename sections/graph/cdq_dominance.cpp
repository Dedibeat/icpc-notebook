// 3D dominance: for each point, count OTHER points with x<=X,y<=Y,z<=Z.
// Complexity: O(n log^2 n) time, O(n) memory (CDQ + Fenwick).
// Pitfalls: exact duplicate points are grouped; coordinates may be negative.
// Usage: vector<long long> ans = dominance_count(points);
struct Point3 { long long x, y, z; };

vector<long long> dominance_count(const vector<Point3>& input) {
    struct Node {
        long long x, y, z, weight, ans;
        int zi;
        vector<int> ids;
    };
    int n = input.size();
    vector<int> order(n); iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return tie(input[a].x, input[a].y, input[a].z) <
               tie(input[b].x, input[b].y, input[b].z);
    });
    vector<Node> a;
    for (int id : order) {
        auto p = input[id];
        if (a.empty() || tie(a.back().x, a.back().y, a.back().z) != tie(p.x, p.y, p.z))
            a.push_back({p.x, p.y, p.z, 0, 0, 0, {}});
        ++a.back().weight;
        a.back().ids.push_back(id);
    }
    vector<long long> zs;
    for (auto& p : a) zs.push_back(p.z);
    sort(zs.begin(), zs.end()); zs.erase(unique(zs.begin(), zs.end()), zs.end());
    for (auto& p : a) {
        p.zi = lower_bound(zs.begin(), zs.end(), p.z) - zs.begin() + 1;
        p.ans = p.weight - 1;
    }
    vector<long long> bit(zs.size() + 1);
    auto add = [&](int i, long long v) { for (; i < (int)bit.size(); i += i&-i) bit[i] += v; };
    auto sum = [&](int i) { long long s=0; for (; i; i-=i&-i) s+=bit[i]; return s; };
    vector<Node> tmp(a.size());
    function<void(int,int)> cdq = [&](int l, int r) {
        if (r-l <= 1) return;
        int m=(l+r)/2; cdq(l,m); cdq(m,r);
        int i=l;
        for (int j=m; j<r; ++j) {
            while (i<m && a[i].y<=a[j].y) add(a[i].zi,a[i].weight), ++i;
            a[j].ans += sum(a[j].zi);
        }
        while (i>l) --i, add(a[i].zi,-a[i].weight);
        merge(a.begin()+l,a.begin()+m,a.begin()+m,a.begin()+r,tmp.begin()+l,
              [](const Node& p,const Node& q){ return p.y<q.y; });
        copy(tmp.begin()+l,tmp.begin()+r,a.begin()+l);
    };
    cdq(0, a.size());
    vector<long long> ans(n);
    for (auto& p : a) for (int id : p.ids) ans[id]=p.ans;
    return ans;
}
