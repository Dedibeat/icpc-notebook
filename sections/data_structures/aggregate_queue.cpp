// Two-stack queue: push back, pop front, aggregate of the whole queue.
// Amortized O(1) per op (each element moves between stacks once); memory O(n).
// Edit V, op and ID. op must be associative with identity ID; it need not be
// commutative or invertible (gcd, min, OR, matrix or affine composition).
// op(older, newer): query() combines front ... back in queue order.
// Pitfalls: pop() needs size() > 0; empty query() returns ID.
// Use: two pointers whose window condition is a gcd/min/... of the window.
// Example: AggQueue q; q.push(12); q.push(18); // query()==6; pop() -> 18
struct AggQueue {
    using V = long long;
    static constexpr V ID = 0;
    static V op(V a, V b) { return gcd(a, b); }
    vector<V> in, inAgg{ID}, outAgg{ID}; // inAgg: back part, outAgg: front part
    void push(V x) { in.push_back(x); inAgg.push_back(op(inAgg.back(), x)); }
    void pop() {
        if (outAgg.size() == 1) { // front part empty: move the back part over
            for (; !in.empty(); in.pop_back())
                outAgg.push_back(op(in.back(), outAgg.back()));
            inAgg.resize(1);
        }
        outAgg.pop_back();
    }
    V query() { return op(outAgg.back(), inAgg.back()); }
    int size() { return in.size() + outAgg.size() - 1; }
};
