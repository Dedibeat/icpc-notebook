// Aho-Corasick counts occurrences of many lowercase patterns in one text.
// Input: add lowercase patterns, build once, then scan lowercase text.
// Effect: duplicate add calls add multiplicity; build fills failure transitions.
// Output: countMatches(text) returns total hits over all pattern copies.
// Complexity: build O(total pattern length*A), match O(text length); O(nodes*A).
// Pitfalls: build fills missing transitions, so do not add patterns afterward.
struct Aho {
    // EDIT ONLY A and idx() for other alphabets; out-of-range chars = UB.
    static const int A = 26;
    static int idx(char ch) { return ch - 'a'; }

    struct Node {
        int nxt[A];
        int link = 0;
        int out = 0;

        Node() {
            memset(nxt, -1, sizeof nxt);
        }
    };

    vector<Node> t;

    Aho() {
        t.push_back(Node());
    }

    void add(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = idx(ch);
            if (t[v].nxt[c] == -1) {
                t[v].nxt[c] = t.size();
                t.push_back(Node());
            }
            v = t[v].nxt[c];
        }
        t[v].out++;
    }

    void build() { // Completes failure transitions; call after all patterns and before matching.
        queue<int> q;

        for (int c = 0; c < A; c++) {
            int u = t[0].nxt[c];
            if (u == -1) t[0].nxt[c] = 0;
            else q.push(u);
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            t[v].out += t[t[v].link].out;

            for (int c = 0; c < A; c++) {
                int u = t[v].nxt[c];
                if (u == -1) {
                    t[v].nxt[c] = t[t[v].link].nxt[c];
                } else {
                    t[u].link = t[t[v].link].nxt[c];
                    q.push(u);
                }
            }
        }
    }

    long long countMatches(const string& s) {
        int v = 0;
        long long ans = 0;
        for (char ch : s) {
            int c = idx(ch);
            v = t[v].nxt[c];
            ans += t[v].out;
        }
        return ans;
    }
};
