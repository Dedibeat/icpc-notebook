// Parallel binary search for predicates monotone over an event prefix.
// Returns smallest prefix length t in [0,events], or events+1 if never true.
// Complexity: O(log(events+2)) full replays; memory O(q+events).
// Pitfalls: apply events in fixed order; reset must fully clear state; check(id)
//           must stay true after becoming true.
// Usage: ans=parallel_bs(q,event_count,reset,apply_event,check_query);
template<class Reset,class Apply,class Check>
vector<int> parallel_bs(int q,int events,Reset reset,Apply apply,Check check) {
    vector<int>lo(q,-1),hi(q,events+1);
    while(true) {
        bool active=false;
        vector<vector<int>>bucket(events+1);
        for(int id=0;id<q;++id) if(lo[id]+1<hi[id]) {
            int mid=(lo[id]+hi[id])/2;
            if(mid<=events) bucket[mid].push_back(id);
            active=true;
        }
        if(!active) return hi;
        reset();
        for(int t=0;t<=events;++t) {
            for(int id:bucket[t]) {
                if(check(id)) hi[id]=t;
                else lo[id]=t;
            }
            if(t<events) apply(t);
        }
    }
}
