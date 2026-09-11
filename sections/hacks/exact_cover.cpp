// Algorithm X with bitmasks: select rows covering every column EXACTLY once.
// <=64 columns; rows are masks. Returns row indices or nullopt (EXACT).
// Worst case exponential; O(columns*rows) per search node, O(columns) stack.
// Zero rows can be ignored; this is exact cover, not ordinary set cover.
// Usage: exactCover(3, {3,4,5}) returns row indices {0,1}.
#include "common.hpp"

optional<vector<int>> exactCover(int columns, const vector<ull>& rows) {
    assert(0 <= columns && columns <= 64);
    ull full = columns == 64 ? ~0ULL : (1ULL << columns)-1;
    for (ull r : rows) assert(!(r & ~full));
    vector<int> chosen;
    function<bool(ull)> dfs = [&](ull covered) {
        if (covered == full) return true;
        int best = -1, count = INT_MAX;
        for (int c = 0; c < columns; ++c) if (!(covered >> c & 1)) {
            int ways = 0;
            for (ull r : rows)
                ways += !(r & covered) && (r >> c & 1);
            if (ways < count) { count = ways; best = c; }
        }
        if (!count) return false;
        for (int i = 0; i < (int)rows.size(); ++i)
            if (!(rows[i] & covered) && (rows[i] >> best & 1)) {
                chosen.push_back(i);
                if (dfs(covered | rows[i])) return true;
                chosen.pop_back();
            }
        return false;
    };
    if (dfs(0)) return chosen;
    return nullopt;
}
