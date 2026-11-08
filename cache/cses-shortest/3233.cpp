#include "bits/stdc++.h"

using namespace std;
int mp[2000001] = {0};
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    int arr[n+1] = {0};
    for(int i = 1;i<=n;i++){
        cin>>arr[i];
        arr[i]^=arr[i-1];
        if(mp[arr[i]]>=5&&mp[arr[i]^arr[i-1]]>=5)continue;
        for(int j = 0;j<i;j++)mp[arr[i]^arr[j]]++;
    }
    int cnt = 0;
    for(int x = 0;x<=2e6;x++){
        if(mp[x])cnt++;
    }
    cout<<cnt<<endl;
    for(int x = 0;x<=2e6;x++){
        if(mp[x])cout<<x<<" ";
    }
}