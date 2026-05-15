struct Aho {
    // NOTE: only for lowercase 'a'..'z'. Other chars index out of bounds.
    static const int A = 26;

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
            int c = ch - 'a';
            if (t[v].nxt[c] == -1) {
                t[v].nxt[c] = t.size();
                t.push_back(Node());
            }
            v = t[v].nxt[c];
        }
        t[v].out++;
    }

    void build() {
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
            int c = ch - 'a';
            v = t[v].nxt[c];
            ans += t[v].out;
        }
        return ans;
    }
};
