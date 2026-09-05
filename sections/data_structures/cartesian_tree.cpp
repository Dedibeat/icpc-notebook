// Min Cartesian tree: inorder is the array; parent value <= child value.
// Complexity: O(n) time/memory using a monotonic stack.
// Pitfalls: strict '>' makes the EARLIER equal value the ancestor; changing
//           the comparison changes duplicate tie behavior.
// Example: a={3,1,2} gives root=1, left[1]=0, right[1]=2.
struct CartesianTree {
    int root=-1;
    vector<int>parent,left,right;
};
CartesianTree cartesian_tree(const vector<long long>& a) {
    int n=a.size();
    CartesianTree t;
    t.parent.assign(n,-1);t.left.assign(n,-1);t.right.assign(n,-1);
    vector<int>st;
    for(int i=0;i<n;++i) {
        int last=-1;
        while(!st.empty() && a[st.back()]>a[i]) last=st.back(),st.pop_back();
        if(!st.empty()) t.right[st.back()]=i,t.parent[i]=st.back();
        if(last!=-1) t.left[i]=last,t.parent[last]=i;
        st.push_back(i);
    }
    if(n) t.root=st.front();
    return t;
}
