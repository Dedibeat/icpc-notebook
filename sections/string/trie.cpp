// Lowercase trie and nonnegative 63-bit xor trie.
// Complexity: O(length) / O(63) per insert, erase, query.
// Pitfalls: lowercase alphabet only; erase only values currently present.
// Usage: Trie t; t.insert(s); BinaryTrie b; b.insert(x); b.max_xor(x).
struct Trie {
    // ---- customize alphabet here -----------------------------------------
    static const int A = 26;
    static int id(char c) { return c-'a'; }
    // ----------------------------------------------------------------------
    struct Node {
        array<int, A> next;
        int pass = 0, end = 0;
        Node() { next.fill(-1); }
    };
    vector<Node> tr{Node()};
    void insert(const string& s) {
        int v = 0; ++tr[v].pass;
        for (char c : s) {
            int x = id(c);
            if (tr[v].next[x] == -1) tr[v].next[x] = tr.size(), tr.emplace_back();
            v = tr[v].next[x]; ++tr[v].pass;
        }
        ++tr[v].end;
    }
    int count_word(const string& s) const {
        int v = 0;
        for (char c : s) {
            int x = id(c);
            if (tr[v].next[x] == -1) return 0;
            v = tr[v].next[x];
        }
        return tr[v].end;
    }
    int count_prefix(const string& s) const {
        int v = 0;
        for (char c : s) {
            int x = id(c);
            if (tr[v].next[x] == -1) return 0;
            v = tr[v].next[x];
        }
        return tr[v].pass;
    }
};

struct BinaryTrie {
    static const int MAX_BIT = 62;
    struct Node { int ch[2] = {-1, -1}, cnt = 0; };
    vector<Node> tr{Node()};
    void add(unsigned long long x, int delta) {
        int v = 0; tr[v].cnt += delta;
        for (int b = MAX_BIT; b >= 0; --b) {
            int bit = x >> b & 1;
            if (tr[v].ch[bit] == -1) tr[v].ch[bit] = tr.size(), tr.push_back(Node());
            v = tr[v].ch[bit]; tr[v].cnt += delta;
        }
    }
    void insert(unsigned long long x) { add(x, 1); }
    void erase(unsigned long long x) { add(x, -1); }
    unsigned long long max_xor(unsigned long long x) const {
        assert(tr[0].cnt > 0);
        int v = 0; unsigned long long ans = 0;
        for (int b = MAX_BIT; b >= 0; --b) {
            int bit = x >> b & 1, want = bit ^ 1, to = tr[v].ch[want];
            if (to != -1 && tr[to].cnt > 0) ans |= 1ULL << b, v = to;
            else v = tr[v].ch[bit];
        }
        return ans;
    }
};
