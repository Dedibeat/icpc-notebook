// Suffix automaton: substring membership, occurrences, distinct substrings.
// Complexity: O(|s|*A) memory here, O(|s|) build/finish for fixed alphabet.
// Pitfalls: lowercase only; add all characters before occurrence queries.
// Usage: SuffixAutomaton sam(s); sam.contains(t); sam.occurrences(t);
struct SuffixAutomaton {
    // ---- customize alphabet here -----------------------------------------
    static const int A = 26;
    static int id(char c) { return c-'a'; }
    // ----------------------------------------------------------------------
    struct State {
        array<int,A> next;
        int link=-1, len=0;
        long long occ=0;
        State() { next.fill(-1); }
    };
    vector<State> st;
    int last;
    bool ready;

    SuffixAutomaton(const string& s="") { init(); for(char c:s) extend(c); }
    void init() { st.assign(1,State()); last=0; ready=false; }
    void extend(char ch) {
        assert(!ready); // occurrence counts have not been propagated yet
        int c=id(ch), cur=st.size(); st.push_back(State());
        st[cur].len=st[last].len+1; st[cur].occ=1;
        int p=last;
        while(p!=-1 && st[p].next[c]==-1) st[p].next[c]=cur,p=st[p].link;
        if(p==-1) st[cur].link=0;
        else {
            int q=st[p].next[c];
            if(st[p].len+1==st[q].len) st[cur].link=q;
            else {
                int clone=st.size(); st.push_back(st[q]);
                st[clone].len=st[p].len+1; st[clone].occ=0;
                while(p!=-1 && st[p].next[c]==q) st[p].next[c]=clone,p=st[p].link;
                st[q].link=st[cur].link=clone;
            }
        }
        last=cur;
    }
    void finish() {
        if(ready) return;
        int mx=0; for(auto& s:st) mx=max(mx,s.len);
        vector<int> cnt(mx+1),order(st.size());
        for(auto& s:st) ++cnt[s.len];
        partial_sum(cnt.begin(),cnt.end(),cnt.begin());
        for(int i=(int)st.size()-1;i>=0;--i) order[--cnt[st[i].len]]=i;
        for(int i=(int)order.size()-1;i>0;--i) {
            int v=order[i]; st[st[v].link].occ+=st[v].occ;
        }
        ready=true;
    }
    int state(const string& s) const {
        int v=0;
        for(char ch:s) { int c=id(ch); if(c<0||c>=A||st[v].next[c]==-1)return -1; v=st[v].next[c]; }
        return v;
    }
    bool contains(const string& s) const { return state(s)!=-1; }
    long long occurrences(const string& s) {
        if(s.empty()) return st[last].len+1;
        finish(); int v=state(s); return v==-1?0:st[v].occ;
    }
    long long distinctSubstrings() const {
        long long ans=0;
        for(int v=1;v<(int)st.size();++v) ans+=st[v].len-st[st[v].link].len;
        return ans;
    }
};
