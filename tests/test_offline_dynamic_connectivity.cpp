#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/offline_dynamic_connectivity.cpp"

using Event = tuple<char, int, int>;
using Edge = OfflineDSU::E;

struct Snapshot {
    vector<int> label;
    vector<long long> value;
};

Snapshot brute(const vector<long long>& values, const set<Edge>& edges) {
    int n = values.size();
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    Snapshot state{vector<int>(n, -1), vector<long long>(n)};
    for (int s = 0; s < n; ++s) {
        if (state.label[s] != -1) continue;
        queue<int> q;
        q.push(s);
        state.label[s] = s;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            state.value[s] ^= values[u];
            for (int v : g[u]) {
                if (state.label[v] != -1) continue;
                state.label[v] = s;
                q.push(v);
            }
        }
    }
    return state;
}

void check(const vector<long long>& values, const vector<Event>& events) {
    OfflineDSU dc(values);
    set<Edge> edges;
    vector<Snapshot> want;
    for (auto [c, u, v] : events) {
        Edge e = minmax(u, v);
        if (c == '+') edges.insert(e);
        if (c == '-') edges.erase(e);
        int time = dc.event(c, u, v);
        assert(time == static_cast<int>(want.size()));
        want.push_back(brute(values, edges));
    }

    int n = values.size();
    for (int run = 0; run < 2; ++run) {
        vector<int> seen(want.size());
        dc.solve([&](int t) {
            assert(0 <= t && t < static_cast<int>(want.size()));
            ++seen[t];
            const auto& [label, value] = want[t];
            for (int u = 0; u < n; ++u) {
                assert(dc.component(u) == value[label[u]]);
                for (int v = 0; v < n; ++v)
                    assert((dc.find(u) == dc.find(v)) == (label[u] == label[v]));
            }
        });
        for (int count : seen) assert(count == 1);
        assert(dc.hist.empty());
        for (int u = 0; u < n; ++u) {
            assert(dc.find(u) == u);
            assert(dc.siz[u] == 1);
            assert(dc.component(u) == values[u]);
        }
    }
}

int main() {
    check({}, {});
    check({-1}, {{'?', 0, 0}});
    check({1LL << 40, 1LL << 40, -3}, {
        {'+', 0, 0}, {'+', 0, 1}, {'+', 1, 2}, {'+', 2, 0},
        {'-', 1, 0}, {'-', 0, 2}, {'?', 0, 2}, {'+', 1, 0},
        {'-', 0, 0}, {'?', 0, 2}, {'-', 1, 2}
    });

    mt19937 rng(12);
    for (int length = 1; length <= 200; ++length) {
        int n = 1 + rng() % 8;
        vector<long long> values(n);
        for (auto& value : values)
            value = static_cast<long long>(rng() % 1001) - 500;

        set<Edge> active;
        vector<Event> events;
        for (int step = 0; step < length; ++step) {
            int u = rng() % n, v = rng() % n;
            Edge e = minmax(u, v);
            int type = rng() % 3;
            char c = '?';
            if (type == 0 && active.insert(e).second) c = '+';
            if (type == 1 && active.erase(e)) c = '-';
            events.emplace_back(c, u, v);
        }
        check(values, events);
    }
}
