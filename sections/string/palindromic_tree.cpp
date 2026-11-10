// Palindromic tree (eertree): online distinct palindromes and occurrences.
// Complexity: O(n*A) memory here, O(n) build and occurrence propagation.
// Input: lowercase characters passed to add in text order.
// Each non-root node is one distinct palindrome. link[v] points to its
// longest proper palindromic suffix. Nodes 0/1 have
// lengths -1/0. Output: add returns the longest suffix node; after
// finishOccurrences(), tree[v].occ is the total count of palindrome v.
// Pitfalls: lowercase only; finish once after all adds, then do not extend.
struct Eertree {
    // ---- customize alphabet here -----------------------------------------
    static const int A=26;
    static int id(char c){return c-'a';}
    // ----------------------------------------------------------------------
    struct Node {
        int len=0,link=0,firstEnd=-1;
        long long occ=0;
        array<int,A>next;
        Node(int length=0):len(length){next.fill(-1);}
    };
    vector<Node>tree;
    vector<int>s;
    string text;
    int suffix;
    bool ready;

    Eertree(const string& str=""){
        init();for(char c:str)add(c);
    }
    void init(){
        tree={Node(-1),Node(0)};tree[0].link=0;tree[1].link=0;s={-1};text.clear();suffix=1;ready=false;
    }
    int getLink(int v,int pos,int c) const { // Internal: returns the longest extendable palindromic suffix node.
        while(s[pos-1-tree[v].len]!=c)v=tree[v].link;
        return v;
    }
    int add(char ch) {
        assert(!ready);
        int c=id(ch);assert(0<=c&&c<A);
        text.push_back(ch);s.push_back(c);
        int pos=s.size()-1,cur=getLink(suffix,pos,c);
        if(tree[cur].next[c]==-1) {
            int now=tree.size();tree.push_back(Node(tree[cur].len+2));
            tree[now].firstEnd=text.size()-1;
            if(tree[now].len==1)tree[now].link=1;
            else {int p=getLink(tree[cur].link,pos,c);tree[now].link=tree[p].next[c];}
            tree[cur].next[c]=now;
        }
        suffix=tree[cur].next[c];++tree[suffix].occ;
        return suffix;
    }
    int distinct() const{return (int)tree.size()-2;}
    int longestSuffix() const{return suffix;}
    string palindrome(int node) const {
        int r=tree[node].firstEnd;
        return text.substr(r-tree[node].len+1,tree[node].len);
    }
    void finishOccurrences() { // Propagates final occurrence counts; call after the last add().
        if(ready)return;
        for(int v=(int)tree.size()-1;v>=2;--v)
            tree[tree[v].link].occ+=tree[v].occ;
        ready=true;
    }
};
