#include<iostream>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
int main()
{
    int n;cin>>n;
    int a[n];
    tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update>l,r;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        r.insert(a[i]);
    }
    long long ans=0;
    for(int i=0;i<n;i++)
    {
        r.erase(a[i]);
        ans+=min(l.order_of_key(a[i]),r.order_of_key(a[i]));
        l.insert(a[i]);
    }
    cout<<ans;
}
